using System;
using Lab05.Entities;
using Lab05.Entities.DatabaseManager;
using Lab05.Services;
using NSubstitute;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab5.Tests;

public class AccountServiceTests
{
    private readonly UserService _userService;

    public AccountServiceTests()
    {
        IDataManager? dataManager = Substitute.For<IDataManager>();
        _userService = new UserService(dataManager);
        dataManager.GetAccount(11111).Returns(new Account(11111, 123));
        _userService.Login(11111, 123);
    }

    [Theory]
    [InlineData(1000)]
    [InlineData(500)]
    public void DepositMoney(int depositAmount)
    {
        _userService.Deposit(depositAmount);

        Assert.Equal(depositAmount, _userService.ViewBalance());
    }

    [Theory]
    [InlineData(10000)]
    [InlineData(2000)]
    public void WithdrawMoneyFail(int withdrawAmount)
    {
        Assert.Throws<ArgumentException>(() =>
        {
            _userService.Withdraw(withdrawAmount);
        });
    }

    [Theory]
    [InlineData(1000, 100, 900)]
    [InlineData(1000, 200, 800)]
    public void WithdrawMoneySuccess(int initialBalance, int withdrawAmount, int expectedBalance)
    {
        _userService.Deposit(initialBalance);
        _userService.Withdraw(withdrawAmount);

        Assert.Equal(expectedBalance, _userService.ViewBalance());
    }
}