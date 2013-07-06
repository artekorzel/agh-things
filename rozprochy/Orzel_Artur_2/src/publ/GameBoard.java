package publ;

import java.io.Serializable;
import java.rmi.RemoteException;

public class GameBoard implements Serializable {
	public static final int BOARD_SIZE = 3;
	
	private GameBoardCell[][] board;
	private IPlayer winner;
	
	public GameBoard() {
		board = new GameBoardCell[BOARD_SIZE][BOARD_SIZE];
		for(int i = 0; i < BOARD_SIZE; ++i) {
			for(int j = 0; j < BOARD_SIZE; ++j) {
				board[i][j] = GameBoardCell.EMPTY;
			}
		}
	}
	
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		for(int i = 0; i < BOARD_SIZE; ++i) {
			for(int j = 0; j < BOARD_SIZE; ++j) {
				builder.append(" ").append(board[i][j].toString()).append(" ");
			}
			builder.append("\n");
		}
		return builder.toString();
	}
	
	public boolean doMoveIfProper(String move, GameBoardCell playerCell, IServerService serverService, 
			IPlayer player) throws RemoteException, PlayerNotAllowedException {
		try {
			int moveNumber = Integer.parseInt(move);
			if(moveNumber >= 0 && moveNumber < BOARD_SIZE * BOARD_SIZE) {
				int y = moveNumber / BOARD_SIZE;
				int x = moveNumber % BOARD_SIZE;
				if(board[y][x].equals(GameBoardCell.EMPTY)) {
					board[y][x] = playerCell;					
					serverService.doMove(player, this);					
					return true;
				}
			}
		} catch(NumberFormatException e) {
			//celowo pusty, zwracamy false
		}
		return false;
	}

	public boolean checkIfFinished(IPlayer playerOne, IPlayer playerTwo) {		
		//przekatna z lewego gornego rogu
		GameBoardCell winnnigCell = board[0][0];
		boolean gameOver = true;
		
		if(!winnnigCell.equals(GameBoardCell.EMPTY)) {
			for(int i = 1; i < BOARD_SIZE && gameOver; ++i) {
				gameOver = winnnigCell.equals(board[i][i]);
			}
			
			if(gameOver) {
				setWinner(playerOne, playerTwo, winnnigCell);
				return true;
			}
		}
		
		//przekatna z prawego gornego rogu
		winnnigCell = board[BOARD_SIZE - 1][0];
		gameOver = true;
		
		if(!winnnigCell.equals(GameBoardCell.EMPTY)) {
			for(int i = 1; i < BOARD_SIZE && gameOver; ++i) {
				gameOver = winnnigCell.equals(board[BOARD_SIZE - i - 1][i]);
			}
			
			if(gameOver) {
				setWinner(playerOne, playerTwo, winnnigCell);
				return true;
			}
		}
		
		//kolumny
		for(int x = 0; x < BOARD_SIZE; ++x) {
			winnnigCell = board[x][0];
			gameOver = true;
			
			if(!winnnigCell.equals(GameBoardCell.EMPTY)) {
				for(int y = 1; y < BOARD_SIZE && gameOver; ++y) {
					gameOver = winnnigCell.equals(board[x][y]);
				}
				
				if(gameOver) {
					setWinner(playerOne, playerTwo, winnnigCell);
					return true;
				}
			}
		}
		
		//wiersze
		for(int y = 0; y < BOARD_SIZE; ++y) {
			winnnigCell = board[0][y];
			gameOver = true;
			
			if(!winnnigCell.equals(GameBoardCell.EMPTY)) {
				for(int x = 1; x < BOARD_SIZE && gameOver; ++x) {
					gameOver = winnnigCell.equals(board[x][y]);
				}
				
				if(gameOver) {
					setWinner(playerOne, playerTwo, winnnigCell);
					return true;
				}
			}
		}
		
		//czy sa puste pola
		for(int i = 0; i < BOARD_SIZE; ++i) {
			for(int j = 0; j < BOARD_SIZE; ++j) {
				if(board[i][j].equals(GameBoardCell.EMPTY)) {
					return false;
				}
			}
		}
		
		return true;
	}

	private void setWinner(IPlayer playerOne, IPlayer playerTwo,
			GameBoardCell winnnigCell) {
		winner = winnnigCell.equals(GameBoardCell.CROSS) ? playerOne : playerTwo;
	}

	public IPlayer getWinner() {
		return winner;
	}
}
