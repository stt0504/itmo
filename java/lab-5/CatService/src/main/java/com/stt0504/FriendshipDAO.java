package com.stt0504;

import com.stt0504.Entities.CatFriendship;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface FriendshipDAO extends JpaRepository<CatFriendship, Long> { }
