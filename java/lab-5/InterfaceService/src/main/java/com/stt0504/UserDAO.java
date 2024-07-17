package com.stt0504;

import com.stt0504.Entities.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface UserDAO extends JpaRepository<User, Long> {
    User findByUsername(String username);
}