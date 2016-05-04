package fr.vmarchaud.matcha.objects;

import java.util.Date;
import java.util.UUID;

import lombok.Data;

@Data
public class Visit {
	
	public UUID		user;
	public UUID		visited;
	public Date		date;
	
}
