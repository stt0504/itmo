package com.stt0504.Console.AccountActions;

import com.stt0504.Console.Action;
import com.stt0504.Transaction.Refill;
import com.stt0504.Transaction.Transaction;

import java.util.Scanner;

/**
 * The RefillAction class represents an action to refill the balance of an account.
 * It extends the Action class and prompts the user to enter the amount to refill.
 */
public class RefillAction extends Action {

    /**
     * Constructor for RefillAction class.
     * @param name The name of the refill action.
     */
    public RefillAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter the amount to refill the account.
     * Creates a refill transaction and executes it.
     * Executes the next action after refilling the account.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter the amount to refill
        System.out.println("Enter the amount to refill: ");
        double amount = sc.nextDouble();

        // Create a refill transaction
        Transaction refill = new Refill(manager.bank, amount, manager.account);

        // Execute the refill transaction
        refill.Execute();

        // Execute the next action
        next.Run();
    }
}
