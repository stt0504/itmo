package com.stt0504;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;


@SpringBootApplication(scanBasePackages = {"com.stt0504"})
@EntityScan(basePackages = "com.stt0504.*")
@EnableJpaRepositories(basePackages = "com.stt0504.*")
public class Main {
    public static void main(String[] args) {
        SpringApplication.run(Main.class, args);
    }
}
