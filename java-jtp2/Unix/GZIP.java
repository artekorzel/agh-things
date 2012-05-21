import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class GZIP {
	private static final int BUF = 2048;
	private static String sciezka;
	private static String sciezkaWzgl;
	private static File p;
	private static ZipOutputStream zos;
	
	public static void decompress(String [] args) {
		ZipInputStream zis = null;
		try {	
			zis = new ZipInputStream(new BufferedInputStream(new FileInputStream(args[1])));
			ZipEntry ze;
			File dir = new File(args[2]);
			dir.mkdirs();
			while((ze = zis.getNextEntry()) != null) {	
				if(ze.isDirectory()) {
					File f = new File(dir.getAbsolutePath() + "/" + ze.getName());
					if(!f.exists()) {
						f.mkdirs();
					}
				} else {
					BufferedOutputStream bos = null;
					try {
						bos = new BufferedOutputStream(new FileOutputStream(dir.getAbsolutePath() + "/" + ze.getName()), BUF);
						byte [] buf = new byte[BUF];
						int i;
						while((i = zis.read(buf, 0, BUF)) != -1) {
							bos.write(buf, 0, i);
						}
					} catch(IOException e) {
						System.err.println("Blad strumienia");
					} finally {
						if(bos != null) {
							try {
								bos.close();			
							} catch(IOException e) {
								System.err.println("Blad zamykania strumienia");
								bos = null;
							}
						}
					}
				}
			}
		} catch(IOException e) {
			System.err.println("Blad strumienia");
		} finally {
			if(zis != null) {
				try {
					zis.close();
				} catch(IOException e) {
					System.err.println("Blad zamykania strumienia");
					zis = null;
				}
			}
		}
	}
	
	public static void compress(String [] args) {
		try {
			p = new File(args[0]);
			p.createNewFile();
			zos = new ZipOutputStream(new BufferedOutputStream(new FileOutputStream(p)));
			
			int i = 1;
			while(i < args.length) {
				File plik = new File(args[i]);
				sciezka = plik.getAbsolutePath();
				sciezkaWzgl = plik.getName();
				if(plik.isDirectory()) {
					compressDir(plik);
				} else {
					compressFile(plik);
				}
				i++;
			}
		} catch(IOException e) {
			System.err.println("Blad strumienia");
		} finally {
			try {
				zos.close();
			} catch(IOException e) {
				System.err.println("Blad zamykania strumienia");
				zos = null;
			}
		}
	}
	
	private static void compressDir(File plik) {
		try {
			ZipEntry ze = new ZipEntry(plik.getAbsolutePath().replace(sciezka, sciezkaWzgl) + "/");
			zos.putNextEntry(ze);
			zos.closeEntry();
			for(File f:plik.listFiles()) {
				if(f.isDirectory()) {
					compressDir(f);
				} else {
					compressFile(f);
				}
			}
		} catch(IOException e) {
			System.err.println("Blad strumienia");
		}
	}
	
	private static void compressFile(File plik) {
		BufferedInputStream bis = null;
		try {
			byte [] buf = new byte[BUF];
			bis = new BufferedInputStream(new FileInputStream(plik), BUF);			
			ZipEntry ze = new ZipEntry(plik.getAbsolutePath().replace(sciezka, sciezkaWzgl));
			zos.putNextEntry(ze);
			
			int i;
			
			while((i = bis.read(buf, 0, BUF)) != -1) {
				zos.write(buf, 0, i);
			}		
			zos.closeEntry();
		} catch(IOException e) {
			System.err.println("Blad strumienia");
		} finally {
			if(bis != null) {
				try {
					bis.close();
				} catch(IOException e) {
					System.err.println("Blad zamykania strumienia");
					bis = null;
				}
			}
		}
	}
	
	public static void main(String [] args) {
		if(args.length != 0) {
			if(args[0].equals("-d")) {
					decompress(args);
			} else {
					compress(args);
			}
		} else {
			System.out.println("nie podano argumentów!");
		}
	}
}
