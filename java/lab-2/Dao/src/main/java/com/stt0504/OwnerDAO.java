package com.stt0504;

import org.hibernate.Session;
import org.hibernate.SessionFactory;

import java.util.List;

public class OwnerDAO {
    private final SessionFactory sessionFactory;

    public OwnerDAO(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    public Owner addOwner(Owner owner) {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            session.persist(owner);
            session.getTransaction().commit();
            return session.get(Owner.class, owner.getId());
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }

    public List<Owner> getAllOwners() {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            List<Owner> owners = session.createQuery("FROM Owner", Owner.class).getResultList();
            session.getTransaction().commit();
            return owners;
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }

    public Owner getOwnerById(Long id) {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            Owner owner = session.get(Owner.class, id);
            session.getTransaction().commit();
            return owner;
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }
}
