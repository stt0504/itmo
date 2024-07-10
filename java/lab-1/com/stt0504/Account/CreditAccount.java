package com.stt0504.Account;

import com.stt0504.User.User;

import java.time.LocalDate;

import static java.lang.Math.abs;

/**
 * The CreditAccount class is an account type that allows a credit to a certain limit. If the balance is negative after the withdrawal transaction, the commission will be debited from the balance.
 * It has attributes such as limit, transaction commission.
 */
public class CreditAccount extends Account {

    /** The limit of credit for the account. */
    private final double limit;

    /** The commission rate applied for credit transactions. */
    private final double commission;

    /**
     * Constructor for CreditAccount class.
     * @param ID The unique identifier of the account.
     * @param startDate The start date of the account.
     * @param endDate The end date of the account.
     * @param limit The overdraft limit for the account.
     * @param commission The commission rate applied for overdraft transactions.
     * @param owner The owner of the account.
     * @param balance The start balance of the account.
     */
    public CreditAccount(int ID, LocalDate startDate, LocalDate endDate, double limit, double commission, User owner, double balance) {
        super(ID, startDate, endDate, owner, balance);
        this.limit = limit;
        this.commission = commission;
    }

    /**
     * Withdraws the specified amount from the account's balance, accounting for credit limit and commission.
     * @param amount The amount to withdraw from the balance.
     * @throws IllegalArgumentException if the credit limit is exceeded.
     */
    public void Withdraw(double amount) {
        if (balance - amount < 0) {
            if (abs(balance - amount - commission) <= limit) {
                balance -= commission;
            } else {
                throw new IllegalArgumentException("Credit limit exceeded");
            }
        }
        balance -= amount;
    }

    /**
     * Updates the account balance by monthly commission.
     * No update for credit account
     */
    @Override
    public void Update() {
    }

    /**
     * Calculates and returns the account balance on the specified date.
     * For credit accounts, the balance remains constant over time, so it returns the current balance.
     * @param date The date for which to calculate the balance.
     * @return The balance of the account on the specified date.
     */
    @Override
    public double CountBalanceAtDate(LocalDate date) {
        return balance;
    }
}
