package com.stt0504;

import org.hibernate.Session;
import org.hibernate.SessionFactory;

import java.util.List;

public class CatDAO {
    private final SessionFactory sessionFactory;

    public CatDAO(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    public Cat addCat(Cat cat) {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            session.persist(cat);
            session.getTransaction().commit();
            return session.get(Cat.class, cat.getId());
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }

    public List<Cat> getAllCats() {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            List<Cat> cats = session.createQuery("FROM Cat", Cat.class).getResultList();
            session.getTransaction().commit();
            return cats;
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }

    public Cat getCatById(Long id) {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            Cat cat = session.get(Cat.class, id);
            session.getTransaction().commit();
            return cat;
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }

    public void addFriendship(Long id1, Long id2) {
        Session session = sessionFactory.openSession();
        session.beginTransaction();
        try {
            CatFriendship friendship = new CatFriendship();
            friendship.setCatId(id1);
            friendship.setFriendId(id2);
            session.persist(friendship);

            CatFriendship friendship2 = new CatFriendship();
            friendship2.setCatId(id2);
            friendship2.setFriendId(id1);
            session.persist(friendship2);

            session.getTransaction().commit();
        } catch (Exception e) {
            session.getTransaction().rollback();
            throw e;
        }
    }
}
