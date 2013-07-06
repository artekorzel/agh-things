package pl.edu.agh.student.aorzel.server;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

import org.omg.CORBA.ORB;
import org.omg.CORBA.ORBPackage.InvalidName;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContextExt;
import org.omg.CosNaming.NamingContextExtHelper;
import org.omg.CosNaming.NamingContextPackage.CannotProceed;
import org.omg.CosNaming.NamingContextPackage.NotFound;
import org.omg.PortableServer.POA;
import org.omg.PortableServer.POAHelper;
import org.omg.PortableServer.POAManagerPackage.AdapterInactive;
import org.omg.PortableServer.POAPackage.ServantAlreadyActive;
import org.omg.PortableServer.POAPackage.ServantNotActive;
import org.omg.PortableServer.POAPackage.WrongPolicy;

import pl.edu.agh.student.aorzel.idl.AFactory;
import pl.edu.agh.student.aorzel.idl.AFactoryHelper;

public class Server {
	public static void main(String[] args) {
		ORB orb = ORB.init(args, null);
		Properties properties = System.getProperties();
		try {
			properties.load(new FileInputStream("./server.config"));
			
			POA rootPOA = POAHelper.narrow(orb
					.resolve_initial_references("RootPOA"));
			rootPOA.the_POAManager().activate();

			AFactoryImpl servant = new AFactoryImpl();
			rootPOA.activate_object(servant);

			org.omg.CORBA.Object servantReference = rootPOA
					.servant_to_reference(servant);
			AFactory factory = AFactoryHelper.narrow(servantReference);

			org.omg.CORBA.Object nameServiceReference = orb
					.string_to_object(properties.getProperty("IOR.Address"));

			NamingContextExt namingContextReference = NamingContextExtHelper
					.narrow(nameServiceReference);

			NameComponent path[] = namingContextReference.to_name(properties.getProperty("Factory.Name"));
			namingContextReference.rebind(path, factory);

			System.out.println("Server start...");
			orb.run();
		} catch (IOException e) {
			System.out.println("Problem with setting properties: " + e.getMessage());
		} catch (AdapterInactive e) {
			System.out.println("Problem with activating POA manager: " + e.getMessage());
		} catch (InvalidName e) {
			System.out.println("Problem with obtaining RootPOA: " + e.getMessage());
		} catch (ServantAlreadyActive e) {
			System.out.println("Problem with activating servant: " + e.getMessage());
		} catch (WrongPolicy e) {
			System.out.println("Problem with policies: " + e.getMessage());
		} catch (ServantNotActive e) {
			System.out.println("Problem with referencing servant: " + e.getMessage());
		} catch (org.omg.CosNaming.NamingContextPackage.InvalidName e) {
			System.out.println("Problem with registering factory(invalid name): " + e.getMessage());
		} catch (NotFound e) {
			System.out.println("Problem with registering factory(not found): " + e.getMessage());
		} catch (CannotProceed e) {
			System.out.println("Problem with registering factory(cannot proceed): " + e.getMessage());
		}
		System.out.println("Server shutdown...");
	}
}