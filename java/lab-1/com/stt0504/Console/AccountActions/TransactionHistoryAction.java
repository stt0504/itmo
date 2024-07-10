package com.stt0504.Console.AccountActions;

import com.stt0504.Console.Action;
import com.stt0504.Transaction.Transaction;
import java.util.List;

/**
 * The TransactionHistoryAction class represents an action to display the transaction history of an account.
 * It extends the Action class and retrieves the list of transactions associated with the account.
 */
public class TransactionHistoryAction extends Action {

    /**
     * Constructor for TransactionHistoryAction class.
     * @param name The name of the transaction history action.
     */
    public TransactionHistoryAction(String name) {
        super(name);
    }

    /**
     * Runs the action by retrieving the list of transactions associated with the account,
     * displaying the transaction history, and executing the next action.
     */
    public void Run() {
        // Retrieve the list of transactions associated with the account
        List<Transaction> transactions = manager.account.GetTransactions();

        // Check if there are no transactions found for this account
        if (transactions.isEmpty()) {
            System.out.println("No transactions found for this account.");
            return;
        }

        // Display the transaction history for the account
        System.out.println("Transaction history for account " + manager.account.getID() + ":");
        for (Transaction transaction : transactions) {
            System.out.println("Date: " + transaction.getDate());
            System.out.println("Type: " + transaction.getClass().getName());
            System.out.println("Status: " + transaction.getStatus());
            System.out.println("Amount: " + transaction.getAmount());
            System.out.println("Result Balance: " + transaction.getResultBalance());
            System.out.println();
        }

        // Execute the next action
        next.Run();
    }
}
