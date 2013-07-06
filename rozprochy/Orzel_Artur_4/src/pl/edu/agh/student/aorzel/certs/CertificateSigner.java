package pl.edu.agh.student.aorzel.certs;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;

import SR.CertSignerPrx;
import SR.CertSignerPrxHelper;
import SR.DataTooLong;
import SR.IncorrectCSRFile;

public class CertificateSigner {

	public static void main(String[] args) {
		if(args.length < 5) {
			System.err.println("Usage: java " + CertificateSigner.class.getName() + " [name] [surname] [certReqFile] [certDestFile] --Ice.Config=[config file]");
			return;
		}
		
		Ice.Communicator ic = Ice.Util.initialize(args);
		Ice.ObjectPrx proxy = ic.propertyToProxy("CertSigner.Proxy");
		CertSignerPrx certSignerProxy = CertSignerPrxHelper.checkedCast(proxy);
		if(certSignerProxy == null) {
			System.err.println("Unknown proxy!");
			return;
		}
		
		FileOutputStream certFile = null;
		
		try {
			byte[] certRequest = readCSR(args[2]);
			byte[] certResponse = certSignerProxy.signCSR(args[0], args[1], certRequest);
			certFile = new FileOutputStream(args[3]);
			certFile.write(certResponse);
		} catch (DataTooLong e) {
			System.err.println("Data to long!");
		} catch (IncorrectCSRFile e) {
			System.err.println("CSR incorrect!");
		} catch (IOException e) {
			System.err.println("Cannot create cert file!");
		} finally {
			ic.destroy();
			
			if(certFile != null) {
				try {
					certFile.close();
				} catch(IOException e) {
					System.err.println("Cannot close the file!");
				}
			}
		}
	}

	private static byte[] readCSR(String fileName) throws IOException {
		FileInputStream reader = null;
		try {
			File file = new File(fileName);
			reader = new FileInputStream(file);
			int bytesRead, bufferSize = 1024;
			StringBuffer stringBuffer = new StringBuffer();
			byte[] buffer = new byte[bufferSize];
			bytesRead = reader.read(buffer);
			while(bytesRead != -1) {
				stringBuffer.append(new String(Arrays.copyOfRange(buffer, 0, bytesRead), "US-ASCII"));
				bytesRead = reader.read(buffer);
			}
			
			return stringBuffer.toString().getBytes("US-ASCII");
		} finally {
			if(reader != null) {
				reader.close();
			}
		}		
	}

}
