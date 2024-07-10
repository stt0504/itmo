package com.stt0504.Bank;

import java.time.LocalDate;
import java.util.NavigableMap;
import java.util.Vector;

/**
 * The CentralBank class represents a central authority responsible for managing banks and their operations.
 */
public class CentralBank {

    /** The list of registered banks under the central bank's authority. */
    private final Vector<Bank> banks = new Vector<>();

    /** The current date managed by the central bank. */
    private LocalDate date;

    /**
     * Creates a new bank with the specified parameters.
     * @param name The name of the bank.
     * @param commission The commission rate applied for transactions.
     * @param percents The map of interest rates for different account types.
     * @param debitPercent The annual percentage rate (APR) for debit accounts.
     */
    public void CreateBank(String name, double commission, NavigableMap<Double, Double> percents, double debitPercent, double creditLimit, double withdrawLimit, double transferLimit) {
        banks.add(new Bank(name, commission, percents, debitPercent, creditLimit, withdrawLimit, transferLimit));
    }

    /**
     * Notifies all registered banks to update their accounts.
     */
    void NotifyBanks() {
        for (Bank bank: banks) {
            bank.Update();
        }
    }
}
