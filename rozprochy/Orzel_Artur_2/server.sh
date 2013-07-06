#!/bin/bash
. properties.conf
SERVER_JAR=TicTacToeRMI-server.jar
java -Djava.rmi.server.codebase=${publicPath} -jar $SERVER_JAR
