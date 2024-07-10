package com.stt0504.Transaction;

import com.stt0504.Account.Account;
import com.stt0504.Bank.Bank;

/**
 * Represents a withdrawal transaction from an account.
 */
public class Withdraw extends Transaction {
    /** The account from which the withdrawal is made. */
    public Account account;

    /**
     * Initializes a new instance of Withdrawal transaction.
     * @param bank The bank associated with the transaction.
     * @param amount The amount to be withdrawn.
     * @param account The account from which the withdrawal is made.
     */
    public Withdraw(Bank bank, double amount, Account account) {
        super(bank, amount);
        this.account = account;
        status = TransactionStatus.CREATED;
    }

    /**
     * Executes the withdrawal transaction.
     * Updates the status of the transaction and processes the withdrawal from the account.
     */
    public void Execute() {
        status = TransactionStatus.WORKING;
        account.AddTransaction(this);
        try {
            bank.Withdraw(account, amount);
            status = TransactionStatus.COMPLETED;
        } catch (Exception e) {
            status = TransactionStatus.FAILED;
            System.out.println(e.getMessage());
        }
    }

    /**
     * Cancels the withdrawal transaction if it has been completed.
     * Refills the amount back to the account.
     */
    public void Cancel() {
        if (status == TransactionStatus.COMPLETED) {
            bank.Refill(account, amount);
            status = TransactionStatus.CANCELLED;
        } else {
            throw new IllegalArgumentException("Cannot cancel an incomplete transaction");
        }
    }
}
