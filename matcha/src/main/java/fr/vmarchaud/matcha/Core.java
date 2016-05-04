package fr.vmarchaud.matcha;

import static spark.Spark.*;

import org.sql2o.Sql2o;

import lombok.Getter;

public class Core {

	// Entry point for this program
	public static void main(String[] args) {
		new Core(args);
	}
	
	@Getter
	public static Core instance;
	
	@Getter
	public static Sql2o database;
	

	public Core(String[] args) {
		instance = this;
		database = new Sql2o("jdbc:mysql://5.196.95.224:3306/matcha", "matcha", "");
		
		port(4242);
		
		after((request, response) -> {
		    response.header("Content-Encoding", "gzip");
		});
		
	}
}
