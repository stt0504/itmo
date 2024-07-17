package com.stt0504;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.Customizer;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configurers.AbstractHttpConfigurer;
import org.springframework.security.crypto.password.NoOpPasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;

import javax.sql.DataSource;
@Configuration
@EnableWebSecurity
public class SecurityConfig {
    @Autowired
    private DataSource dataSource;
    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                .cors(AbstractHttpConfigurer::disable)
                .csrf(AbstractHttpConfigurer::disable)
                .authorizeHttpRequests((authorize) -> authorize
                        .requestMatchers("/cats/all").hasRole("ADMIN")
                        .requestMatchers("/cats/get_by_id").hasRole("ADMIN")
                        .requestMatchers("/owners/get_all").hasRole("ADMIN")
                        .requestMatchers("/owners/get_by_id").hasRole("ADMIN")
                        .requestMatchers("/cats/add_friendship").hasRole("ADMIN")
                        .requestMatchers("/**").hasAnyRole("ADMIN", "USER")
                        .anyRequest().authenticated())
                .httpBasic(Customizer.withDefaults());

        return http.build();
    }

    @Autowired
    public void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.jdbcAuthentication()
                .dataSource(dataSource)
                .passwordEncoder(NoOpPasswordEncoder.getInstance())
                .usersByUsernameQuery("select username, password, status from users where username=?")
                .authoritiesByUsernameQuery("select u.username, CONCAT('ROLE_', r.role) from users u inner join roles r on u.user_id = r.user_id where u.username=?");
    }
}