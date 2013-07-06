
import org.python.core.PyList;
import org.python.core.PyObject;
import org.python.core.PyString;
import org.python.util.PythonInterpreter;
import java.lang.StringBuffer;

public class PoleceniaJava {
	private PyObject builder;
	
	public PoleceniaJava(){
		PythonInterpreter interpreter = new PythonInterpreter();
        interpreter.exec("from PoleceniaPython import PoleceniaPython");
        builder = interpreter.get("PoleceniaPython");
	}
	
	public Polecenia stworz(){
		PyObject object = builder.__call__();
		return (Polecenia)object.__tojava__(Polecenia.class);
	}
	
	public String mail(PyList adresy, PyList opcje, PyList tresci) {
		Polecenia polecenia = stworz();
		StringBuffer s = new StringBuffer();
		int i;
		for(i = 0; i < adresy.size(); ++i)
			s.append(polecenia.mail((PyString)adresy.pyget(i),
					(PyString)opcje.pyget(i),(PyString)tresci.pyget(i)))
					.append("\n");

		return s.toString();
	}
}
