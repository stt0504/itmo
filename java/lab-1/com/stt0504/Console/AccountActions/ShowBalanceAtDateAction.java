package com.stt0504.Console.AccountActions;

import com.stt0504.Console.Action;

import java.time.LocalDate;
import java.util.Scanner;

/**
 * The ShowBalanceAtDateAction class represents an action to display the balance of an account at a specific date.
 * It extends the Action class and prompts the user to enter a date in the format YYYY-MM-DD.
 */
public class ShowBalanceAtDateAction extends Action {

    /**
     * Constructor for ShowBalanceAtDateAction class.
     * @param name The name of the show balance at date action.
     */
    public ShowBalanceAtDateAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter a date in the format YYYY-MM-DD,
     * displaying the balance of the account at that date,
     * and executing the next action.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter a date in the format YYYY-MM-DD
        System.out.println("Enter the date in the format YYYY-MM-DD: ");
        String dateString = sc.nextLine();
        LocalDate date = LocalDate.parse(dateString);

        // Display the balance of the account at the specified date
        System.out.print("Your balance at " + dateString + " will be: ");
        System.out.println(manager.account.CountBalanceAtDate(date));

        // Execute the next action
        next.Run();
    }
}
