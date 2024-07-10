package com.stt0504.Console.AccountActions;

import com.stt0504.Console.Action;
import com.stt0504.Transaction.Transaction;
import com.stt0504.Transaction.Withdraw;

import java.util.Scanner;

/**
 * The WithdrawAction class represents an action to withdraw funds from an account.
 * It extends the Action class and prompts the user to enter the amount to withdraw.
 */
public class WithdrawAction extends Action {

    /**
     * Constructor for WithdrawAction class.
     * @param name The name of the withdraw action.
     */
    public WithdrawAction(String name) {
        super(name);
    }

    /**
     * Runs the action by prompting the user to enter the amount to withdraw,
     * creating a withdrawal transaction, and executing it.
     * Executes the next action after completing the withdrawal.
     */
    public void Run() {
        Scanner sc = new Scanner(System.in);

        // Prompt the user to enter the amount to withdraw
        System.out.println("Enter the amount to withdraw: ");
        double amount = sc.nextDouble();

        // Create a withdrawal transaction with the current date, status, bank, amount, result balance, and account
        Transaction withdraw = new Withdraw(manager.bank, amount, manager.account);

        // Execute the withdrawal transaction
        withdraw.Execute();

        // Execute the next action
        next.Run();
    }
}
