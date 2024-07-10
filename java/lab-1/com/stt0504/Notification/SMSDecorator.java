package com.stt0504.Notification;

import com.stt0504.User.User;

public class SMSDecorator implements Notification {

    public SMSDecorator(Notification wrappee) {
        this.wrappee = wrappee;
    }
    public Notification wrappee;

    @Override
    public void notify(User user) {
        wrappee.notify(user);
        notifySMS(user);
    }

    public void notifySMS(User user) { }
}
