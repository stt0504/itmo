package com.stt0504.Console.BankActions;

import com.stt0504.Console.Action;

import java.util.Scanner;

/**
 * The LoginAction class represents an action to log in a user to the bank system.
 * It extends the Action class and prompts the user to enter their login credentials.
 */
public class LoginAction extends Action {

    /**
     * Constructor for LoginAction class.
     * @param name The name of the login action.
     */
    public LoginAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter their login credentials and logging them in.
     * Sets the logged-in user to the data manager of the next action and executes it.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter their login
        System.out.println("Enter the login: ");
        String login = sc.nextLine();

        // Prompt the user to enter their password
        System.out.println("Enter the password: ");
        String password = sc.nextLine();

        // Find the user based on the provided login credentials
        next.manager = manager;
        next.manager.user = manager.bank.FindUser(login, password);

        // Execute the next action
        next.Run();
    }
}
