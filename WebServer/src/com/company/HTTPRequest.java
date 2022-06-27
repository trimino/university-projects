package com.company;

import javax.imageio.ImageIO;
import javax.imageio.stream.IIOByteBuffer;
import javax.imageio.stream.ImageInputStream;
import javax.xml.crypto.Data;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.Socket;
import java.nio.ByteOrder;
import java.security.cert.CRL;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class HTTPRequest implements Runnable{

    // Get the working director and the operating system name
    private final static String workDir          = System.getProperty("user.dir");
    private final static String os               = System.getProperty("os.name");

    private final static String error404 = "<html>\n" + "\t<head>\n" + "\t\t<title>Not Found</title>\n" + "\t</head>\n" + "\t<body>\n" + "\t\t<p><b>404 Error: PAGE NOT FOUND</b></p>\n" + "\t</body>\n</html>";
    private final static Map<String, String> oldNewFileName = Map.of("change.html", "more/newIndex.html");
    private final static String serverCode      = "Multi-Threaded/1.0.1 (Mint)";
    private final static String[] responseCode = {"200", "301", "404"};
    private final static String responseHeader = "HTTP/1.1 ";
    private final static String CRLF = "\r\n";

    private Date date;
    private Socket socket;
    private BufferedReader bufferedReader;
    private DataOutputStream dataOutputStream;
    private SimpleDateFormat simpleDateFormat;

    public HTTPRequest(Socket socket) throws Exception{
        this.socket = socket;
        this.date = new Date();
        this.simpleDateFormat   = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
        this.dataOutputStream   = new DataOutputStream(this.socket.getOutputStream());
        this.bufferedReader     = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
    }

    @Override
    public void run() {
        // Display contents from the HTTP Request message
        String requestLine      = null;
        String headerLine       = null;

        // Variables to help construct HTTP Response
        String filename         = null;
        String filename301      = null;
        String statusLine       = null;
        String contentType      = null;
        String entityBody       = null;
        StringTokenizer tokens  = null;
        FileInputStream fis     = null;
        BufferedImage img       = null;
        boolean fileExists      = false;
        boolean error301Exists  = false;

        try {
            // Get the request line of the client's request message
            requestLine = bufferedReader.readLine();
            System.out.println();
            System.out.println(requestLine);

            // Get and display the header of the client's request message
            while ((headerLine = bufferedReader.readLine()).length() != 0)
                System.out.println(headerLine);

            // Extract the filename from the requestLine
            tokens = new StringTokenizer(requestLine);
            tokens.nextToken();
        }catch (IOException e){
            System.err.println("ERROR: In getting request message and displaying message");
            e.printStackTrace();
        }


        try {
            // Check to see if there is a file that is requested by the client
            if (tokens.hasMoreTokens()) {
                filename301 = tokens.nextToken();
                error301Exists = check301Error(filename301.substring(1));

                if (!error301Exists) {
                    // Determine the OS and find the working directory and the index.html file
                    if (os.equals("Linux"))
                        filename = String.format("%s/com/company/%s", workDir, filename301);
                    else
                        filename = String.format("%s\\com\\company\\%s", workDir, filename301.substring(1));

                    // Open the requested file
                    fis = new FileInputStream(filename);
                    fileExists = true;
                }else{
                    fileExists = false;
                    filename = "DNE";
                }

            }else{
                fileExists  = false;
                filename    = "xyz";
            }
        }catch (FileNotFoundException e){
            System.err.println("File Not found: " + filename + '\n');
            fileExists = false;
            filename = "DNE";
        }

        // Construct status line for response header: if the file exists then 200 OK
        if (fileExists)
            statusLine = responseHeader + responseCode[0] + " OK";
        else if (error301Exists)
            statusLine = responseHeader + responseCode[1] + "Moved Permanently";
        else {
            statusLine = responseHeader + responseCode[2];
            entityBody = error404;
        }


        try {
            System.out.println();

            // Determine the file contents
            contentType = String.format("Content-Type: %s", fileType(filename));

            // Send the appropriate response messages
            if (fileExists)
                sendResponse(statusLine, contentType, filename, fis);
            else if (error301Exists)
                send301Response(statusLine, oldNewFileName.get(filename301.substring(1)));
            else
                send404Response(statusLine, entityBody);

            System.out.println("----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        }catch (IOException e){
            e.printStackTrace();
        }catch (Exception e){
            System.err.println("ERROR: In the sendBytes method");
        }finally {
            try{
                if (this.dataOutputStream != null)
                    this.dataOutputStream.close();

                if (this.bufferedReader != null)
                    this.bufferedReader.close();

                if (this.socket != null)
                    this.socket.close();
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }


    /*
     * Name         : check301Error
     * Parameters   : The filename that the user requests
     * Description  : Checks to see if the file has been moved
     * Returns      : True if the file has been moved and false if it hasnt
     */
    private boolean check301Error(String filename){
        return oldNewFileName.containsKey(filename);
    }


    /*
     * Name         : sendBytes
     * Parameters   : The fileInput is the inputStream to the file that was requested by the client and the output stream sends the file to the client's input
     * Description  : Creates a 6k buffer and sends the copy requested file to the client's input stream using the output stream
     * Returns      : void
     */
    private void sendBytes(FileInputStream fileInput) throws Exception{
        // Construct a 6k buffer to hold bytes on their way to the socket
        byte[] buffer = new byte[6144];
        int bytes = 0;

        // Copy requested file into the socket's output stream
        while ((bytes = fileInput.read(buffer)) != -1) {
            this.dataOutputStream.write(buffer, 0, bytes);
            this.dataOutputStream.flush();
        }
    }


    /*
     * Name         : fileType
     * Parameters   : The filename that the client has requested
     * Description  : Determines the file extension and checks for : htm, html, jpg, png, and css extensions. If none are applicable return default
     * Returns      : A string
     */
    private static String fileType(String filename){
        if (filename.endsWith(".htm") || filename.endsWith(".html"))
            return "text/html";

        else if (filename.endsWith(".jpeg") || filename.endsWith(".jpg"))
            return "image/jpeg";

        else if (filename.endsWith(".png"))
            return "image/png";

        else if (filename.endsWith(".css"))
            return "text/css";

        else
            return "application/octet-stream";
    }


    /*
     * Name         : sendResponse
     * Parameters   : 1st parameter is the status line of the request and contentType is one of the return values from fileType
     * Description  : Sends an HTTP Response as long as the file exists. This methods assumes that you have checked that file exists
     * Returns      : void
     */
    private void sendResponse(String statusLine, String contentType, String filename, FileInputStream fis) throws Exception, IOException{
        // Send the status line
        System.out.println(statusLine);
        this.dataOutputStream.writeBytes(statusLine);
        this.dataOutputStream.writeBytes(CRLF);

        // Send the date the request was made
        System.out.println(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the server line
        System.out.println("Server: " + this.serverCode);
        this.dataOutputStream.writeBytes(String.format("Server: %s", this.serverCode));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the date the file was last modified
        File file = new File(filename);
        System.out.println("Last Modified: " + this.simpleDateFormat.format(file.lastModified()));
        this.dataOutputStream.writeBytes(String.format("Last Modified: %s", this.simpleDateFormat.format(file.lastModified())));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the content line
        System.out.println(contentType);
        this.dataOutputStream.writeBytes(contentType);
        this.dataOutputStream.writeBytes(CRLF);

        // Send the length of content
        System.out.println("Content-Length: " + fis.getChannel().size() + " bytes");
        this.dataOutputStream.writeBytes(String.format("Content-Length: %s bytes", fis.getChannel().size()));
        this.dataOutputStream.writeBytes(CRLF);

        // Send a blank line to indicate the end of the header lines
        this.dataOutputStream.writeBytes(CRLF);

        // Send the file to the client
        sendBytes(fis);
    }


    /*
     * Name         : send301Response
     * Parameters   : 1st parameter is the status line of the message the data is the htmlErrorCode and the oldFilename is a key to the Map
     * Description  : Constructs and sends a 301 HTTPResponse message
     * Returns      : void
     */
    private void send301Response(String statusLine, String newLocation)throws IOException {
        // Send the status line
        System.out.println(statusLine);
        this.dataOutputStream.writeBytes(statusLine);
        this.dataOutputStream.writeBytes(CRLF);

        // Send the date the request was made
        System.out.println(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the server line
        System.out.println("Server: " + serverCode);
        this.dataOutputStream.writeBytes(String.format("Server: %s", serverCode));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the content of the message
        System.out.println("Content-Type: text/html");
        this.dataOutputStream.writeBytes("Content-Type: text/html");
        this.dataOutputStream.writeBytes(CRLF);

        // Send the new location
        System.out.println("Location: " + newLocation);
        this.dataOutputStream.writeBytes(String.format("Location: %s", newLocation));
        this.dataOutputStream.writeBytes(CRLF);

        // Send a blank line to indicate the end of the header lines
        this.dataOutputStream.writeBytes(CRLF);

        // Ensure all data has been sent
        this.dataOutputStream.flush();
    }


    /*
     * Name         : send404Response
     * Parameters   : statusLine is the status line in http response and the htmlErrorCode is the what will be displayed to the client's web browser
     * Description  : Constructs and sends the HTTP Response to the client
     * Returns      : void
     */
    private void send404Response(String statusLine, String htmlErrorCode) throws IOException{
        // Send the status line
        System.out.println(statusLine);
        this.dataOutputStream.writeBytes(statusLine);
        this.dataOutputStream.writeBytes(CRLF);

        // Send the date the request was made
        System.out.println(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(String.format("Date: %s", this.date.toString()));
        this.dataOutputStream.writeBytes(CRLF);

        // Send the content line
        System.out.println("Content-Type: text/html");
        this.dataOutputStream.writeBytes("Content-Type: text/html");
        this.dataOutputStream.writeBytes(CRLF);

        // Send a blank line to indicate the end of the header lines
        this.dataOutputStream.writeBytes(CRLF);

        // Send the html error code
        System.out.println(htmlErrorCode);
        this.dataOutputStream.writeBytes(htmlErrorCode);
    }

}
