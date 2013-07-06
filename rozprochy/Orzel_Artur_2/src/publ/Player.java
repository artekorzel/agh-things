package publ;

import java.io.Serializable;

public class Player implements IPlayer, Serializable {

	private String nick;
	private IMoveListener moveListener;

	@Override
	public String getNick() {
		return nick;
	}

	public void setNick(String nick) {
		this.nick = nick;
	}

	@Override
	public IMoveListener getMoveListener() {
		return moveListener;
	}

	public void setMoveListener(IMoveListener moveListener) {
		this.moveListener = moveListener;
	}
	
	@Override
	public int hashCode() {
		return nick.hashCode();
	}

	@Override
	public boolean equals(Object obj) {
		if(!(obj instanceof IPlayer)) {
			return false;
		}
		return nick.equals(((IPlayer)obj).getNick());
	}
}
