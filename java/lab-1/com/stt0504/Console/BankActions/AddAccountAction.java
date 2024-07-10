package com.stt0504.Console.BankActions;

import com.stt0504.Account.AccountType;
import com.stt0504.Console.Action;

import java.time.LocalDate;
import java.util.Scanner;

/**
 * The AddAccountAction class represents an action to add a new account for the user.
 * It extends the Action class and prompts the user to enter the type of account to be created.
 */
public class AddAccountAction extends Action {

    /**
     * Constructor for AddAccountAction class.
     * @param name The name of the add account action.
     */
    public AddAccountAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter the type of account to be created and adding the account accordingly.
     * Redirects to the next action after adding the account.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter the type of account
        System.out.println("Enter type (CREDIT, DEBIT, DEPOSIT): ");
        String type = sc.nextLine();

        // Create account based on the user's input
        System.out.println("Enter the end date in the format YYYY-MM-DD: ");
        String dateString = sc.nextLine();
        LocalDate date = LocalDate.parse(dateString);
        switch (type.toUpperCase()) {
            case "CREDIT":
                manager.bank.CreateAccount(manager.user, AccountType.CREDIT, LocalDate.now(), date, 0);
                break;
            case "DEBIT":
                System.out.println("Enter type (CREDIT, DEBIT, DEPOSIT): ");
                manager.bank.CreateAccount(manager.user, AccountType.DEBIT, LocalDate.now(), date, 0);
                break;
            case "DEPOSIT":
                manager.bank.CreateAccount(manager.user, AccountType.DEPOSIT, LocalDate.now(), date, 0);
                break;
            default:
                System.out.println("Incorrect type");
                Run(); // Retry if incorrect type is entered
                break;
        }

        // Set the data manager of the next action and execute it
        next.manager = manager;
        next.Run();
    }
}
