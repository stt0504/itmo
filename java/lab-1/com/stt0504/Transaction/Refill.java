package com.stt0504.Transaction;

import com.stt0504.Account.Account;
import com.stt0504.Bank.Bank;

/**
 * The Refill class represents a transaction to refill funds into an account.
 * It extends the Transaction class.
 */
public class Refill extends Transaction {

    private final Account account;

    /**
     * Constructor for Refill class.
     * @param bank The bank associated with the refill transaction.
     * @param amount The amount to be refilled.
     * @param account The account to which the refill transaction is applied.
     */
    public Refill(Bank bank, double amount, Account account) {
        super(bank, amount);
        this.account = account;
    }

    /**
     * Executes the refill transaction by adding the transaction to the account,
     * refilling the account with the specified amount, and updating the transaction status.
     * Handles exceptions if the refill operation fails.
     */
    public void Execute() {
        status = TransactionStatus.WORKING;
        account.AddTransaction(this);
        try {
            bank.Refill(account, amount);
            status = TransactionStatus.COMPLETED;
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
            status = TransactionStatus.FAILED;
        }
    }

    /**
     * Cancels the refill transaction by withdrawing the amount from the account.
     * Throws an exception if the transaction is incomplete.
     */
    public void Cancel() {
        if (status == TransactionStatus.COMPLETED) {
            bank.Withdraw(account, amount);
            status = TransactionStatus.CANCELLED;
        } else {
            throw new IllegalArgumentException("Cannot cancel an incomplete transaction");
        }
    }
}
