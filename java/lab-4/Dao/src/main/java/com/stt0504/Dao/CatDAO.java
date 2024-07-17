package com.stt0504.Dao;

import com.stt0504.Entities.Cat;
import com.stt0504.Entities.Color;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface CatDAO extends JpaRepository<Cat, Long> {
    @Query("SELECT c FROM Cat c WHERE (:breed IS NULL OR c.breed = :breed) " +
            "AND (:ownerId IS NULL OR c.owner.id = :ownerId) " +
            "AND (:color IS NULL OR c.color = :color) ")
    List<Cat> findByParameters(@Param("ownerId") Long ownerId,
                               @Param("breed") String breed,
                               @Param("color") Color color);
}
