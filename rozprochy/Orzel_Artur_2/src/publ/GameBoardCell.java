package publ;

import java.io.Serializable;

public enum GameBoardCell implements Serializable {
	EMPTY, NOUGHT, CROSS;
	
	@Override
	public String toString() {
		switch(this) {
		case NOUGHT: return "O";
		case CROSS: return "X";
		default: return "-";
		}
	}
}
