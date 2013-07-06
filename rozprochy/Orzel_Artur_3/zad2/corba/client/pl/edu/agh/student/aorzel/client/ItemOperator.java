package pl.edu.agh.student.aorzel.client;

import java.io.IOException;

import org.omg.CORBA.Any;
import org.omg.CORBA.ORB;

import pl.edu.agh.student.aorzel.idl.Item;

public class ItemOperator {
	private static ORB orb;

	public static void setOrb(ORB orb) {
		ItemOperator.orb = orb;
	}

	public static void operateOnItemA(Item item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: void actionA(in float a, out long b)");

		if (!operationDone) {
			org.omg.CORBA.Request request = item._request("actionA");
			request.set_return_type(orb
					.get_primitive_tc(org.omg.CORBA.TCKind.tk_void));

			float inArg = 3.14f;
			request.add_in_arg().insert_float(inArg);

			Any outArg = request.add_out_arg();
			outArg.type(orb.get_primitive_tc(org.omg.CORBA.TCKind.tk_long));

			request.invoke();

			if (request.env().exception() == null) {
				System.out.println("Item - called operation: actionA\n"
						+ "given argument: " + inArg
						+ "\nreturned value as argument: "
						+ outArg.extract_long() + "\n");
			} else {
				System.out.println("Error occured: " + request.env().exception().getMessage());
			}
		}
	}

	public static void operateOnItemB(Item item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: float actionB(in string a)");

		if (!operationDone) {
			org.omg.CORBA.Request request = item._request("actionB");
			request.set_return_type(orb
					.get_primitive_tc(org.omg.CORBA.TCKind.tk_float));

			String inArg = "3.141592";
			request.add_in_arg().insert_string(inArg);

			request.invoke();

			if (request.env().exception() == null) {
				System.out.println("Item - called operation: actionB\n"
						+ "given argument: " + inArg + "\nreturned value: "
						+ request.return_value().extract_float() + "\n");
			} else {
				System.out.println("Error occured: " + request.env().exception().getMessage());
			}
		}

	}

	public static void operateOnItemC(Item item) throws IOException {
		boolean operationDone = operateOnItem(item,
				"3: void actionC(inout long a, out short b)");

		if (!operationDone) {
			org.omg.CORBA.Request request = item._request("actionC");
			request.set_return_type(orb
					.get_primitive_tc(org.omg.CORBA.TCKind.tk_void));

			int inArg = 40000;
			Any inOutArg = request.add_inout_arg();
			inOutArg.insert_long(inArg);

			Any outArg = request.add_out_arg();
			outArg.type(orb.get_primitive_tc(org.omg.CORBA.TCKind.tk_short));

			request.invoke();

			if (request.env().exception() == null) {
				System.out.println("Item - called operation: actionC\n"
						+ "given argument: " + inArg
						+ "\nreturned value in first argument: "
						+ inOutArg.extract_long()
						+ "\nreturned value in second argument: "
						+ outArg.extract_short() + "\n");
			} else {
				System.out.println("Error occured: " + request.env().exception().getMessage());
			}
		}

	}

	private static boolean operateOnItem(Item item, String specificOperation) throws IOException {
		System.out.println("Choose operation to do:\n1: string name()\n2: long get_item_age()\n"
				+ specificOperation + "\n[rest] return\n");
		String operation = Client.READER.readLine();

		if (operation.equals("1")) {
			org.omg.CORBA.Request request = item._request("_get_name");
			request.set_return_type(orb
					.get_primitive_tc(org.omg.CORBA.TCKind.tk_string));
			request.invoke();

			if (request.env().exception() == null) {
				System.out.println("Item name: "
						+ request.return_value().extract_string() + "\n");
			} else {
				System.out.println("Error occured: " + request.env().exception().getMessage());
			}
		} else if (operation.equals("2")) {
			org.omg.CORBA.Request request = item._request("get_item_age");
			request.set_return_type(orb
					.get_primitive_tc(org.omg.CORBA.TCKind.tk_long));
			request.invoke();

			if (request.env().exception() == null) {
				System.out.println("Item age: "
						+ request.return_value().extract_long() + "\n");
			} else {
				System.out.println("Error occured: " + request.env().exception().getMessage());
			}
		} else if (operation.equals("3")) {
			return false;
		}

		return true;
	}

}
