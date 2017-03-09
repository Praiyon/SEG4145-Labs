import java.io.*;
import java.net.*;
import java.util.Scanner;

import javax.swing.JOptionPane;

public class lab4alt {
	
	private static final int PORT = 9876;

	/*
	 * Main method to start the ServerSocket, Listen for Clients,
	 * and handle communication between Sender / Receiver
	 */
	public static void main(String args[]) throws IOException {
		
		int[] message = new int[2];
		
		try (
			
			// Create the server socket for the Receiver
			ServerSocket receiverSocket = new ServerSocket(PORT);
			
			// Create the socket for the sender by accepting connections
			Socket senderSocket = receiverSocket.accept();
				
			// Create output stream to sender
			PrintWriter out = new PrintWriter(senderSocket.getOutputStream(), true);
			
			// Create input stream from sender
			BufferedReader in = new BufferedReader(new InputStreamReader(senderSocket.getInputStream()));
			
		) {
			
			// Create string to store input
			String inputLine;
			
			// Print port information
			System.out.println("Listening on port " + PORT);
             
            // Send initial message to Sender to keep loop active
            out.println();
 
            // While input is received
            while ((inputLine = in.readLine()) != null) {

            	try {
            		
            		// Reading from System.in
        			Scanner reader = new Scanner(System.in);  
        			
        			// Print possible commands
        			System.out.print("Enter the correct number to select an operation: \n"
	            					+ "1 - Move the robot forward.\n"
	            					+ "2 - Move the robot backward.\n"
	            					+ "3 - Rotate the robot clockwise.\n"
	            					+ "4 - Rotate the robot counter clockwise.\n"
	            					+ "5 - Read the distance to the nearest object.\n"
	            					+ "6 - Read temperature values.\n"
	            					+ "7 - Quit\n");
        			
        			// Scans the next token of the input as an int.
        			int command = reader.nextInt();
        			
        			// Pass command chosen to function which further prompts user
        			// and stores result (Format: {command, additional})
        			message = processInput(command);
     
					// Send the result to robot
					out.println(1);
					
				} catch (NullPointerException e) {
					System.out.println("Nothing entered, closing connection");
					System.exit(-1);
				}
                
            }
			
		} catch (IOException e) {
			// Could not listen on a given port
			System.err.println("Could not listen on port " + PORT);
            System.exit(-1);
		} 	    
		
	}
	
	private static int[] processInput(int command) {
		int[] result = new int[2];
		
		// Ask for further input based on command chosen
		// then return result
		
		return result;
	}
	
}
