import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.text.SimpleDateFormat;
import java.util.*;

public class Lab4Alt extends JFrame{

    public static int command = -1;
    public static int additionalCommand;

    public static void main(String[] args) {

        JFrame frame = new JFrame("SEG4145 Lab 5");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(new GridLayout(5, 3));

        // Create first row
        frame.add(new JLabel("", JLabel.CENTER));
        frame.add(new JLabel("Select an Operation:", JLabel.CENTER));
        frame.add(new JLabel("", JLabel.CENTER));

        // Create second row
        createButton("Move Forward", 1, frame);
        createButton("Move Backward", 2, frame);
        createButton("Rotate Clockwise", 3, frame);

        // Create third row
        createButton("Rotate Counter Clockwise", 4, frame);
        createButton("Read Distance", 5, frame);
        createButton("Read Temperature", 6, frame);

        // Create fourth row
        frame.add(new JLabel("", JLabel.CENTER));
        JLabel operation = new JLabel("Last Operation: ", JLabel.CENTER);
        frame.add(operation);
        frame.add(new JLabel("", JLabel.CENTER));

        // Create fifth row
        frame.add(new JLabel("", JLabel.CENTER));
        JLabel timestamp = new JLabel("Timestamp: ", JLabel.CENTER);
        frame.add(timestamp);
        frame.add(new JLabel("", JLabel.CENTER));

        frame.pack();
        frame.setVisible(true);

        while (true) {

            operation.setText("Last Operation: " + command);
            timestamp.setText("Timestamp: " + new SimpleDateFormat("dd/mm/yy HH:mm").format(new Date()));
            System.out.println(command);
            System.out.println(additionalCommand);

        }
    }

    private static void createButton(String text, int val, JFrame frame) {
        JButton btn = new JButton(text);
        btn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e)
            {
                // Update command
                command = val;

                // Update additional command based on command
                if (command == 1 || command == 2) {
                    String distance = JOptionPane.showInputDialog("Enter Distance (0 to 20):");
                    additionalCommand = Integer.parseInt(distance);
                } else if (command == 3 || command == 4) {
                    String degrees = JOptionPane.showInputDialog("Enter Degrees (0 to 359):");
                    additionalCommand = Integer.parseInt(degrees);
                } else if (command == 6) {
                    String tempType = JOptionPane.showInputDialog("Enter Temperature Type (1 - Celsius, 2 - Fahrenheit):");
                    additionalCommand = Integer.parseInt(tempType);
                } else {
                    additionalCommand = 0;
                }
            }
        });
        frame.add(btn);
    }

    private static void getAdditional() {
        // Do something
    }
}