package pl.edu.agh.student.aorzel.client;

import java.io.IOException;

import MiddlewareTestbed.ItemPrx;


public class ItemOperator {
	private static Ice.Communicator ic;

	public static void setCommunicator(Ice.Communicator ic) {
		ItemOperator.ic = ic;
	}

	public static void operateOnItemA(ItemPrx item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: void actionA(float a, out int b)");

		if (!operationDone) {
			Ice.OutputStream out = new Ice.OutputStreamI(ic);
			out.startEncapsulation();
			float inArg = 3.14f;
			out.writeFloat(inArg);
			out.endEncapsulation();
			byte[] inParams = out.finished();
			Ice.ByteSeqHolder outParams = new Ice.ByteSeqHolder();

			if (item.ice_invoke("actionA", Ice.OperationMode.Normal, inParams, outParams)) {
				Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		        in.startEncapsulation();
		        int result = in.readInt();
		        in.endEncapsulation();
				System.out.println("Item - called operation: actionA\n"
						+ "given argument: " + inArg
						+ "\nreturned value as argument: "
						+ result + "\n");
			} else {
				serveException(outParams);
			}
		}
	}

	public static void operateOnItemB(ItemPrx item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: float actionB(string a)");

		if (!operationDone) {
			Ice.OutputStream out = new Ice.OutputStreamI(ic);
			out.startEncapsulation();
			String inArg = "3.141592";
			out.writeString(inArg);
			out.endEncapsulation();
			byte[] inParams = out.finished();
			Ice.ByteSeqHolder outParams = new Ice.ByteSeqHolder();

			if (item.ice_invoke("actionB", Ice.OperationMode.Normal, inParams, outParams)) {
				Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		        in.startEncapsulation();
		        float result = in.readFloat();
		        in.endEncapsulation();
				System.out.println("Item - called operation: actionB\n"
						+ "given argument: " + inArg + "\nreturned value: "
						+ result + "\n");
			} else {
				serveException(outParams);
			}
		}

	}

	public static void operateOnItemC(ItemPrx item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: void actionC(int a1, out int a2, out short b)");

		if (!operationDone) {
			Ice.OutputStream out = new Ice.OutputStreamI(ic);
			out.startEncapsulation();
			int inArg = 40000;
			out.writeInt(inArg);
			out.endEncapsulation();
			byte[] inParams = out.finished();
			Ice.ByteSeqHolder outParams = new Ice.ByteSeqHolder();

			if (item.ice_invoke("actionC", Ice.OperationMode.Normal, inParams, outParams)) {
				Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		        in.startEncapsulation();
		        int result1 = in.readInt();
		        short result2 = in.readShort();
		        in.endEncapsulation();
				System.out.println("Item - called operation: actionC\n"
						+ "given argument: " + inArg
						+ "\nreturned value in first argument: "
						+ result1
						+ "\nreturned value in second argument: "
						+ result2 + "\n");
			} else {
				serveException(outParams);
			}
		}

	}

	private static boolean operateOnItem(ItemPrx item, String specificOperation) throws IOException {
		System.out.println("Choose operation to do:\n1: idempotent string name()\n2: idempotent int get_item_age()\n"
				+ specificOperation + "\n[rest] return\n");
		String operation = Client.READER.readLine();

		Ice.ByteSeqHolder outParams = new Ice.ByteSeqHolder();
		if (operation.equals("1")) {
			if (item.ice_invoke("name", Ice.OperationMode.Idempotent, new byte[0], outParams)) {
				Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		        in.startEncapsulation();
		        String result = in.readString();
		        in.endEncapsulation();
				System.out.println("Item name: " + result + "\n");
			} else {
				serveException(outParams);
			}
		} else if (operation.equals("2")) {			
			if (item.ice_invoke("get_item_age", Ice.OperationMode.Idempotent, new byte[0], outParams)) {
				Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		        in.startEncapsulation();
		        int result = in.readInt();
		        in.endEncapsulation();
				System.out.println("Item age: " + result + "\n");
			} else {
				serveException(outParams);
			}
		} else if (operation.equals("3")) {
			return false;
		}

		return true;
	}

	private static void serveException(Ice.ByteSeqHolder outParams) {
		Ice.InputStream in = Ice.Util.createInputStream(ic, outParams.value);
		try {
		    in.startEncapsulation();
		    in.throwException();
		} catch (Ice.UserException e) {
			System.out.println("Unknown error occured: " + e.getMessage());
		}
	}

}
