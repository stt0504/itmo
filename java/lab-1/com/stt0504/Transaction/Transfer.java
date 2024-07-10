package com.stt0504.Transaction;

import com.stt0504.Account.Account;
import com.stt0504.Bank.Bank;

/**
 * The Transfer class represents a transaction to transfer funds between accounts.
 * It extends the Transaction class and provides functionality to execute and cancel the transfer.
 */
public class Transfer extends Transaction {

    /**
     * The sender account from which funds are transferred.
     */
    private final Account sender;

    /**
     * The receiver account to which funds are transferred.
     */
    private final Account receiver;

    /**
     * Constructor for Transfer class.
     * Initializes the date, bank, amount, result balance, sender account, and receiver account.
     * @param bank The bank associated with the transfer.
     * @param amount The amount of funds to transfer.
     * @param sender The sender account from which funds are transferred.
     * @param receiver The receiver account to which funds are transferred.
     */
    public Transfer(Bank bank, double amount, Account sender, Account receiver) {
        super(bank, amount);
        this.sender = sender;
        this.receiver = receiver;
    }

    /**
     * Executes the transfer transaction by adding the transaction to both sender and receiver accounts,
     * transferring funds between accounts, and updating the transaction status.
     */
    public void Execute() {
        status = TransactionStatus.WORKING;
        sender.AddTransaction(this);
        receiver.AddTransaction(this);
        try {
            bank.Transfer(sender, receiver, amount);
            status = TransactionStatus.COMPLETED;
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
            status = TransactionStatus.FAILED;
        }
    }

    /**
     * Cancels the transfer transaction by reversing the transfer of funds between sender and receiver accounts.
     * If the transaction is completed, the funds are transferred back from the receiver to the sender.
     */
    public void Cancel() {
        if (status == TransactionStatus.COMPLETED) {
            bank.Transfer(receiver, sender, amount);
            status = TransactionStatus.CANCELLED;
        } else {
            throw new IllegalArgumentException("Cannot cancel an incomplete transaction");
        }
    }
}
