package com.company;

import javax.net.ssl.SSLSession;
import java.io.*;
import java.net.*;
import java.net.http.HttpClient;
import java.net.http.HttpHeaders;
import java.net.http.HttpRequest;
import java.time.Duration;
import java.util.*;


public class Server {

    public static void main(String[] args) {

	    int PORT = 8080;
	    ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(PORT);
            serverSocket.setReuseAddress(true);

            while (true){
                Socket clientSocket = serverSocket.accept();

                HTTPRequest httpRequest = new HTTPRequest(clientSocket);

                new Thread(httpRequest).start();
            }
        }catch (IOException e){
            e.printStackTrace();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            try {
                if (serverSocket != null) {
                    serverSocket.close();
                }
            }catch (IOException e){
                e.printStackTrace();
            }
        }


    }
}
