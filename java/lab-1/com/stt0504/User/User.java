package com.stt0504.User;

import com.stt0504.Account.Account;
import com.stt0504.Notification.BaseNotification;
import com.stt0504.Notification.EmailDecorator;
import com.stt0504.Notification.Notification;
import com.stt0504.Notification.SMSDecorator;
import lombok.Getter;

import java.util.List;

@Getter

public class User {
    private final String _name;
    private final String _surname;
    private final String _address;

    private final String login;
    private final String password;
    private final String _passportNumber;

    private User(String name, String surname, String address, String passportNumber, String login, String password) {
        _name = name;
        _surname = surname;
        _address = address;
        _passportNumber = passportNumber;
        this.login = login;
        this.password = password;
    }

    public static class Builder {
        private String _name;
        private String _surname;
        private String _address;
        private String _passportNumber;
        private String _login;
        private String _password;
        private List<Account> _accounts;

        public Builder setName(String name) {
            _name = name;
            return this;
        }

        public Builder setSurname(String surname) {
            _surname = surname;
            return this;
        }

        public Builder setAddress(String address) {
            _address = address;
            return this;
        }

        public Builder setPassportNumber(String passportNumber) {
            _passportNumber = passportNumber;
            return this;
        }

        public Builder setLogin(String login) {
            _login = login;
            return this;
        }

        public Builder setPassword(String password) {
            _password = password;
            return this;
        }

        public Builder setAccounts(List<Account> accounts) {
            _accounts = accounts;
            return this;
        }

        public User build() {
            if (_name == null) {
                throw new NullPointerException("Name can not be null");
            }
            if (_surname == null) {
                throw new NullPointerException("Surname can not be null");
            }
            return new User(_name, _surname, _address, _passportNumber, _login, _password);
        }
    }

    public boolean IsQuestionable() {
        return (_address != null && _passportNumber != null);
    }

    public void receiveNotification() {
        Notification notification = new BaseNotification();
        notification = new EmailDecorator(notification);
        notification = new SMSDecorator(notification);

        notification.notify(this);
    }
}
