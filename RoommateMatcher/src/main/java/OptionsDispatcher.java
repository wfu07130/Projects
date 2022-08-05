import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.io.Serial;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Servlet implementation class SearchDispatcher
 */

@WebServlet("/OptionsDispatcher")
public class OptionsDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;

    /**
     * Default constructor.
     */
    public OptionsDispatcher() {
    }

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    	
    	try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            //TODO check if you've done the initialization
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    	
    	String url = "jdbc:mysql://localhost/final_project"; 
    	String user = "root"; 
    	String pwd = "root";  //your secret database pwd
    	
    	String display = "";
    	
    	String sql = "SELECT * "
    					+ "FROM user_info ";
    	
    	String userEmail = "";
    	Cookie[] cookies = null;
    	cookies = request.getCookies();
    	
		int idx = 0;
		boolean found = false;
		if(cookies != null) {
			for(int i = 0; i < cookies.length; i++) {
	  			if((cookies[i].getName()).trim().equals("ck_email")) {
	  				found = true;
	  				break;
	  			}
	  			idx++;
	  		}
		}
		
		int userID = 0;
		int minAge = 0;
		int maxAge = 0;
		if(found) {
			sql += "WHERE NOT email = ? AND age <= ? AND age >= ?";
			userEmail = cookies[idx].getValue();	
			String query = "SELECT user_id, min_roommate_age, max_roommate_age FROM user_info WHERE email = ? ";
	    	try (Connection conn = DriverManager.getConnection(url, user, pwd);
	    			PreparedStatement ps = conn.prepareStatement(query);) {
	    		
	    		ps.setString(1, userEmail);    		
				ResultSet rs = ps.executeQuery();
				rs.next();
				userID = rs.getInt("user_id");
				minAge = rs.getInt("min_roommate_age");
				maxAge = rs.getInt("max_roommate_age");
	    	}
	    	
	    	catch (SQLException ex ) {
	    		System.out.println("SQLException" + ex.getMessage());
	    	}
		}
		
    	try (Connection conn = DriverManager.getConnection(url, user, pwd);
        		PreparedStatement ps = conn.prepareStatement(sql);) {
    		if(found) {
    			ps.setString(1, userEmail);
    			ps.setInt(2, maxAge);
    			ps.setInt(3, minAge);
    		}
        	ResultSet rs= ps.executeQuery();
        	if(!rs.isBeforeFirst()) {
        		display += "<h1 style=\"text-align:center; margin-top: 20px;\">No potential roommates yet!</h1>";
        		request.setAttribute("display", display);
        		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/matching.jsp"); 
        		dispatcher.forward(request, response); 
        		return;
        	}
        	else {
        		display += "<div class=\"container-fluid\">\n"
        				+ "        <div class =\"row flex-wrap\" id=\"bruh\">";
        	}
        	while(rs.next()) {
        		boolean alreadyLiked = false;
        		
        		if(found) {
        			String isPresentSql = "SELECT * FROM response_table WHERE user_id = ? AND other_id = ?";
            		try (Connection conn2 = DriverManager.getConnection(url, user, pwd);
                    		PreparedStatement ps2 = conn2.prepareStatement(isPresentSql);) {
            			ps2.setInt(1, userID);
            			ps2.setInt(2, rs.getInt("user_id"));
            			ResultSet rs2 = ps2.executeQuery();
            			if(rs2.next()) {
            				alreadyLiked = true;
            			}
            		}
        		}
        		
        		
        		String gender = rs.getString("gender");
        		String image = "";
        		if(gender.equals("female")) {
        			image = "female.png";
        		}
        		else if(gender.equals("male")) {
        			image = "male.png";
        		}
        		display += "<div class=\"col-lg-3\">"
        				+ "            <div class=\"poster\">"
        				+ "                <img class=\"photo\" src=\"" + image + "\">"
        				+ "                <div class=\"metrics\">"
        				+ "                    <p>Age: " + rs.getInt("age") + "</p>"
        				+ "                    <p>Housing Style: " + rs.getString("housing_style") + "</p>"
        				+ "                    <p>About me: "+ rs.getString("biography") + "</p>"
        				+ "                </div>"
        				+ "            </div>"
        				+ "            <div class=\"info\">"
        				+ "                <p>"+ rs.getString("full_name") + "</p>"
        				+ "                <p>Budget: "+ rs.getInt("budget") + "</p>";
        		if(!alreadyLiked) {
        			display += "			<form action=\"MatchedDispatcher\" method=\"GET\">"
        					+ "             <button class=\"btn btn-primary\" name=\"other_id\" value=\"" + rs.getInt("user_id") + "\"type=\"submit\">Match!</button>"
            				+ "				</form> ";
        		}
        		else {
        			display += "<p>Already Liked!</p>";
        		}
        			display += "            </div>"
        					+ "        </div>";
        	}
        		
        		
    	}
    	catch (SQLException ex) {
        	System.out.println("SQLException " + ex.getMessage() + sql);
        }
    	request.setAttribute("display", display);
		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/matching.jsp"); 
		dispatcher.forward(request, response); 
    }
    	
    	
    	
    	
    			
        // TODO

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // TODO Auto-generated method stub
        doGet(request, response);
    }
}