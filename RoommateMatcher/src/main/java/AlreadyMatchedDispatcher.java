
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

@WebServlet("/AlreadyMatchedDispatcher")
public class AlreadyMatchedDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;

    /**
     * Default constructor.
     */
    public AlreadyMatchedDispatcher() {
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
    	PrintWriter out = response.getWriter();
    	String url = "jdbc:mysql://localhost/final_project"; 
    	String user = "root"; 
    	String pwd = "root";  //your secret database pwd
    	
    	String display = "";
    	int userID = 0;
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
		
		if(!found) {
			String errorMessage = "<p style=\"background-color:#FFCCCB;text-align:center;padding: 15px;\">"
        			+ "Please log in or register before trying to match.</p>";
			out.println(errorMessage);
    		request.getRequestDispatcher("/index.jsp").include(request, response);
    		return;
		}
    	
    	userEmail = cookies[idx].getValue();
    	// set the userID from the cookie
    	String query = "SELECT user_id FROM user_info WHERE email = ? ";
    	try (Connection conn = DriverManager.getConnection(url, user, pwd);
    			PreparedStatement ps = conn.prepareStatement(query);) {
    		ps.setString(1, userEmail);    		
			ResultSet rs1 = ps.executeQuery();
			rs1.next();
			userID = rs1.getInt("user_id");
    	}
    	catch (SQLException ex ) {
    		System.out.println("SQLException" + ex.getMessage());
    		ex.printStackTrace();
    	}
    	
    	// Search through matches table for all of your matches
    	String sql4 = "SELECT other_id FROM matches_table WHERE user_id = ?";
    	try (Connection conn = DriverManager.getConnection(url, user, pwd);
        		PreparedStatement ps4 = conn.prepareStatement(sql4);) {
    		ps4.setInt(1, userID);
    		ResultSet rs4 = ps4.executeQuery();
    		if(!rs4.isBeforeFirst()) {
        		display += "<h1 style=\"text-align:center; margin-top: 20px;\">No matches yet!</h1>";
        		request.setAttribute("display", display);
        		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/matching.jsp"); 
        		dispatcher.forward(request, response); 
        		return;
        	}
    		else {
    			display += "<div class=\"container-fluid\">\r\n"
    					+ "        <div class =\"row flex-wrap\" id=\"bruh\">";
    		}
    		while (rs4.next())
    		{
    			// Search for all the info about your matched person i
	    		String sql5 = "SELECT * FROM user_info WHERE user_id = ?";
	        	try (Connection conn2 = DriverManager.getConnection(url, user, pwd);
	            		PreparedStatement ps5 = conn2.prepareStatement(sql5);) {
	        		ps5.setInt(1, rs4.getInt("other_id"));
	        		ResultSet rs5 = ps5.executeQuery();
	        		rs5.next();
	        		
            		String gender = rs5.getString("gender");
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
            				+ "                    <p>Age: " + rs5.getInt("age") + "</p><br>"
            				+ "                    <p>Housing Style: " + rs5.getString("housing_style") + "</p><br>"
            				+ "                    <p>About me: "+ rs5.getString("biography") + "</p>"
            				+ "                </div>"
            				+ "            </div>"
            				+ "            <div class=\"info\">"
            				+ "                <p>"+ rs5.getString("full_name") + "</p>"
            				+ "                <p>Budget: "+ rs5.getInt("budget") + "</p>"
            				+ "				   <p><a href=\"mailto:"+ rs5.getString("email")+"\">Email them here!</p>"
            				+ "            </div>"
            				+ "        </div>";
	        	}
	        	catch (SQLException ex ) {
	        		System.out.println("SQLException" + ex.getMessage());
	        		ex.printStackTrace();
	        	}
        	}
    	}
    	catch (SQLException ex ) {
    		System.out.println("SQLException" + ex.getMessage());
    		ex.printStackTrace();
    	}
    	request.setAttribute("display", display);
		RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/AlreadyMatched.jsp"); 
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
