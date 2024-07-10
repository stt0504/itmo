package com.stt0504.Notification;

import com.stt0504.User.User;

public class EmailDecorator implements Notification {

    public EmailDecorator(Notification wrappee) {
        this.wrappee = wrappee;
    }
    public Notification wrappee;
    @Override
    public void notify(User user) {
         wrappee.notify(user);
         notifyEmail(user);
    }

    public void notifyEmail(User user) { }
}
