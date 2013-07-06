public enum Operation {	
	SEND_ONE_BYTE_NUMBER(4) {
		@Override
		public void parseValueToSend() throws NumberFormatException {
			String numberString = System.console().readLine(
					"Podaj jednobajtowa liczbe do wyslania:\n");
			value = Byte.parseByte(numberString);
		}

		@Override
		protected void consume(String dataString) throws NumberFormatException {
			value = Byte.parseByte(dataString.trim());
			System.out.println("Odebrano: " + value.byteValue());
		}
	},

	SEND_TWO_BYTE_NUMBER(6) {
		@Override
		public void parseValueToSend() throws NumberFormatException {
			String numberString = System.console().readLine(
					"Podaj dwubajtowa liczbe do wyslania:\n");
			value = Short.parseShort(numberString);
		}

		@Override
		protected void consume(String dataString) {
			value = Short.parseShort(dataString.trim());
			System.out.println("Odebrano: " + value.shortValue());
		}
	},

	SEND_FOUR_BYTE_NUMBER(11) {
		@Override
		public void parseValueToSend() throws NumberFormatException {
			String numberString = System.console().readLine(
					"Podaj czterobajtowa liczbe do wyslania:\n");
			value = Integer.parseInt(numberString);
		}

		@Override
		public void consume(String dataString) {
			value = Integer.parseInt(dataString.trim());
			System.out.println("Odebrano: " + value.intValue());
		}
	},

	END_WORK(0) {

		@Override
		public void parseValueToSend() throws NumberFormatException {
			return; // zakonczenie programu, nie wymaga ustawiania wartosci
		}

		@Override
		public void prepareToSendOrStop() {
			Client.setWorking(false); // ustaw zmienna odpowiadajaca za
										// zakonczenie programu
		}

		@Override
		protected void consume(String dataString) { // ta metoda nigdy nie
													// powinna zostac wywolana
			throw new UnsupportedOperationException("Metoda zabroniona!");
		}
	};

	protected Number value;
	protected int requiredBytes;

	private Operation(int requiredBytes) {
		this.requiredBytes = requiredBytes;
	}

	public static Operation valueOfOperation(int bytesToSend) {
		switch (bytesToSend) {
		case 1:
			return SEND_ONE_BYTE_NUMBER;
		case 2:
			return SEND_TWO_BYTE_NUMBER;
		case 4:
			return SEND_FOUR_BYTE_NUMBER;
		default:
			return END_WORK;
		}
	}

	public void obtainValueToSend() {
		boolean correctNumber = false;
		while (!correctNumber) {
			try {
				parseValueToSend();
				correctNumber = true;
			} catch (NumberFormatException e) {
				System.out.println("Wartosc niepoprawna, sprobuj ponownie:\n");
			}
		}
	}

	public abstract void parseValueToSend() throws NumberFormatException;

	public void prepareToSendOrStop() {
		Client.setToSend(String.format("%" + requiredBytes + "d", value)
				.getBytes());
	}

	public void consumeAfterReceive(byte[] data, int numberOfReceivedBytes) {

		String dataString = new String(data);
		try {
			checkIfBadReceivedData(numberOfReceivedBytes, dataString);
			consume(dataString);
		} catch (NumberFormatException e) {
			System.err.println("Odebrano nieprawidlowe dane: " + dataString);
		} catch (UnsupportedOperationException e) {
			System.err.println("Nieprawidlowa operacja!");
		}
	}

	protected void checkIfBadReceivedData(int numberOfReceivedBytes,
			String dataString) {
		if (requiredBytes <= 0 
				|| numberOfReceivedBytes != requiredBytes
				|| dataString.endsWith(" ") 
				|| dataString.endsWith("\t")
				|| dataString.endsWith("\n")) {
			throw new NumberFormatException();
		}
	}

	protected abstract void consume(String dataString)
			throws NumberFormatException, UnsupportedOperationException;
}