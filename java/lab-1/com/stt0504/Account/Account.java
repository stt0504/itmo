/**
 * The Entities.Account package contains classes related to user accounts.
 */
package com.stt0504.Account;

import com.stt0504.User.User;
import com.stt0504.Transaction.Transaction;
import lombok.Getter;

import java.time.LocalDate;
import java.util.*;

/**
 * The abstract class Account represents common characteristics for all types of accounts.
 * Each account has a unique identifier, balance, start date, end date, owner and a list of transactions with this account.
 */
@Getter
public abstract class Account {

    /** The unique identifier of the account. */
    protected int ID;

    /** The current balance of the account. */
    protected double balance;

    /** The start date of the account. */
    protected LocalDate startDate;

    /** The end date of the account. */
    protected LocalDate endDate;

    /** The list of transactions with this account. */
    protected Vector<Transaction> transactions;

    /** The owner of this account. */
    protected User owner;

    /**
     * Constructor for the Account class.
     * @param ID The unique identifier of the account.
     * @param startDate The start date of the account.
     * @param endDate The end date of the account.
     * @param owner The owner of the account.
     * @param balance The start balance of the account.
     */
    public Account(int ID, LocalDate startDate, LocalDate endDate, User owner, double balance) {
        this.ID = ID;
        this.balance = balance;
        this.startDate = startDate;
        this.endDate = endDate;
        this.transactions = new Vector<>();
        this.owner = owner;
    }

    /**
     * Abstract method Update updates the balance of account at the end of month.
     */
    public abstract void Update();

    /**
     * Abstract method CountBalanceAtDate calculates the balance of the account at the specified date.
     * @param date The date for which to calculate the balance.
     * @return The balance of the account at the specified date.
     */
    public abstract double CountBalanceAtDate(LocalDate date);


    /**
     * Refills the account balance by the specified amount.
     * @param amount The amount to refill the balance by.
     */
    public void Refill(double amount) {
        balance += amount;
    }

    /**
     * Abstract method Withdraw withdraws the specified amount from the account's balance.
     * @param amount The amount to withdraw from the balance.
     */
    public abstract void Withdraw(double amount);

    /**
     * Method AddTransaction adds a transaction to the list of transactions of the account.
     * @param transaction The transaction to add.
     */
    public void AddTransaction(Transaction transaction) {
        transactions.add(transaction);
    }

    /**
     * Method GetTransactions returns the list of transactions of the account.
     * @return The list of transactions of the account.
     */
    public Vector<Transaction> GetTransactions() {
        return transactions;
    }
}
