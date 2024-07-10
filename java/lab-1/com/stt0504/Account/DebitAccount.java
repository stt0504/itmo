package com.stt0504.Account;

import com.stt0504.User.User;

import java.time.LocalDate;

/**
 * The debitAccount class is an account type that allows users to spend only the money that is available in the account.
 */
public class DebitAccount extends InterestBearingAccount {

    /**
     * Constructor for DebitAccount class.
     * @param ID The unique identifier of the account.
     * @param startDate The start date of the account.
     * @param endDate The end date of the account.
     * @param percent The annual percentage rate for calculating interest.
     * @param owner The owner of the account.
     * @param balance The start balance of the account.
     */
    public DebitAccount(int ID, LocalDate startDate, LocalDate endDate, double percent, User owner, double balance) {
        super(ID, startDate, endDate, percent, owner, balance);
    }

    /**
     * Withdraws the specified amount from the account's balance.
     * @param amount The amount to withdraw from the balance.
     */
    public void Withdraw(double amount) {
        if (balance - amount < 0) {
                throw new IllegalArgumentException("Not enough money");
            }
        balance -= amount;
    }
}