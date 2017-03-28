import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class Lab4Alt extends JFrame{

    public static int command;
    public static int additionalCommand;

    public static void main(String[] args) {

        while (true) {
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
            createButton("Rotate Counter Clockwise", 1, frame);
            createButton("Read Distance", 2, frame);
            createButton("Read Temperature", 3, frame);

            // Create fourth row
            frame.add(new JLabel("", JLabel.CENTER));
            frame.add(new JLabel("Operation: ", JLabel.CENTER));
            frame.add(new JLabel("", JLabel.CENTER));

            // Create fifth row
            frame.add(new JLabel("", JLabel.CENTER));
            frame.add(new JLabel("Time: ", JLabel.CENTER));
            frame.add(new JLabel("", JLabel.CENTER));

            frame.pack();
            frame.setVisible(true);

            System.out.println(command);

        }
    }

    private static void createButton(String text, int val, JFrame frame) {
        JButton btn = new JButton(text);
        btn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e)
            {
                String addtional = JOptionPane.showInputDialog("Additional Information");
                command = val;
                JDialog d = new JDialog(frame, Integer.toString(command), true);
                d.setLocationRelativeTo(frame);
                d.setVisible(true);
            }
        });
        frame.add(btn);
    }

    private static void getAdditional() {
        // Do something
    }
}