package com.stt0504;

import com.stt0504.Entities.Owner;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface OwnerDAO extends JpaRepository<Owner, Long> { }
