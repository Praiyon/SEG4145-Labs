import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Lab4 {
	
	private static final int PORT = 9876;

	/*
	 * Main method to start the ServerSocket, Listen for Clients,
	 * and handle communication between Sender / Receiver
	 */
	public static void main(String args[]) throws IOException {
		
		// Store message to be passed to robot
		int[] message = new int[2];
		
		// Reading from System.in
		Scanner reader = new Scanner(System.in);  
		
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
        			
        			// Check for incorrect input
        			if (command == 7) {
        				System.out.println("Quit selected, quiting now.");
        			} else if (command > 7 || command < 1) {
        				System.out.println("Incorrect input, ensure int from 1 to 7 is used.");
        			}
        			
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
            
            // Close scanner
			reader.close();
			
		} catch (IOException e) {
			// Could not listen on a given port
			System.err.println("Could not listen on port " + PORT);
            System.exit(-1);
		} 	    
		
	}
	
	/*
	 * Method that takes user entered command as input
	 * and prompts the user for any additional required information
	 * in order to be sent to the robot
	 */
	private static int[] processInput(int command) {
		
		// Reading from System.in
		Scanner reader = new Scanner(System.in); 
		
		int[] result = new int[2];
		
		// Store command as first entry
		result[0] = command;
		
		// Store any readings
		int additionalCommand;
		
		if (command == 1 || command == 2) { // Move forward or backward
			// Prompt user for distance
			System.out.println("Enter the distance in cm: ");
			
			// Read user input
			additionalCommand = reader.nextInt();
			
			// Store result
			result[1] = additionalCommand;
		} else if (command == 3 || command == 4) { // Rotate clockwise or counter-clockwise
			// Prompt user for degrees
			System.out.println("Enter the degrees to turn: ");
			
			// Read user input
			additionalCommand = reader.nextInt();
			
			// Store result
			result[1] = additionalCommand;
		} else if (command == 5) { // Read sonar
			// Notify user of sonar value being read
			System.out.println("Sonar will be read.");
			
			// Return arbitrary int
			result[1] = 0;
		} else if (command == 6) { // Read temperature
			// Prompt for temperature type
			System.out.print("Enter temperature type you wish to receive: \n"
        					+ "1 - Celcius.\n"
        					+ "2 - Fahrenheit.\n"
        					+ "3 - Both.\n");
			
			// Read user input
			additionalCommand = reader.nextInt();
			
			// Incorrect value
			if (additionalCommand > 3 || additionalCommand < 1) {
				System.out.println("Incorrect value.");
			} else {
				// Store result
				result[1] = additionalCommand;
			}
		} 
		
		// Close scanner
		reader.close();
		
		// Return the resulting array
		return result;
	}
	
}
