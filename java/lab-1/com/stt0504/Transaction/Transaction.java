package com.stt0504.Transaction;

import com.stt0504.Bank.Bank;
import lombok.Getter;

import java.time.LocalDate;

/**
 * The Transaction class represents a generic financial transaction.
 * It is an abstract class providing basic functionality for all types of transactions.
 */
@Getter
public abstract class Transaction {

    /**
     * The date of the transaction.
     */
    protected final LocalDate date;

    /**
     * The status of the transaction.
     */
    protected TransactionStatus status;

    /**
     * The bank associated with the transaction.
     */
    protected final Bank bank;

    /**
     * The amount of the transaction.
     */
    protected double amount;

    /**
     * The resulting balance after executing the transaction.
     */
    protected double resultBalance;

    /**
     * Constructor for Transaction class.
     * Initializes the date, bank, amount, and sets the transaction status to CREATED.
     * @param bank The bank associated with the transaction.
     * @param amount The amount of the transaction.
     */
    public Transaction(Bank bank, double amount) {
        this.date = LocalDate.now();
        this.bank = bank;
        this.amount = amount;
        this.status = TransactionStatus.CREATED;
    }

    /**
     * Executes the transaction.
     * Each subclass must provide its own implementation of this method.
     */
    public abstract void Execute();

    /**
     * Cancels the transaction.
     * Each subclass must provide its own implementation of this method.
     */
    public abstract void Cancel();
}
