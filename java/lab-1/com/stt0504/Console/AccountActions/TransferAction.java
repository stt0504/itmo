package com.stt0504.Console.AccountActions;

import com.stt0504.Console.Action;
import com.stt0504.Transaction.Transaction;
import com.stt0504.Transaction.Transfer;

import java.util.Scanner;

/**
 * The TransferAction class represents an action to transfer funds between accounts.
 * It extends the Action class and prompts the user to enter the amount to transfer.
 */
public class TransferAction extends Action {

    /**
     * Constructor for TransferAction class.
     * @param name The name of the transfer action.
     */
    public TransferAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter the amount to transfer,
     * creating a transfer transaction, and executing it.
     * Executes the next action after completing the transfer.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter the amount to transfer
        System.out.println("Enter the amount to transfer: ");
        double amount = sc.nextDouble();

        // Create a transfer transaction with the current date, bank, amount, sender account, and receiver account
        Transaction transfer = new Transfer(manager.bank, amount, manager.account, manager.account);

        // Execute the transfer transaction
        transfer.Execute();

        // Execute the next action
        next.Run();
    }
}
