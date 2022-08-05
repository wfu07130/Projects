import jakarta.servlet.RequestDispatcher;
import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletContext;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import Util.Helper;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.Serial;
import java.sql.*;

/**
 * Servlet implementation class LoginDispatcher
 */
@WebServlet("/LoginDispatcher")
public class LoginDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     * response)
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
    	try {
    		Class.forName("com.mysql.cj.jdbc.Driver");
    	}
    	catch (ClassNotFoundException e) {
    		e.printStackTrace();
    	}
    	
    	String email = null;
    	String password = null;
    	email = request.getParameter("user_email");
    	password = request.getParameter("user_password");
    	String errorMessage = "<p style=\"background-color:#FFCCCB;text-align:center;padding: 15px;\">"
    			+ "Invalid email or password. Please try again.</p>";
    	
    	
    	PrintWriter out = response.getWriter();
    	
    	if(password == null || password.length() == 0 || password.equals("")) {
    		out.println(errorMessage);
    		request.getRequestDispatcher("/userLogin.html").include(request, response);
    		return;
    	}
    	
    	if(email == null || email.length() == 0 || email.equals("") || email.indexOf("@") == -1) {
    		out.println(errorMessage);
    		request.getRequestDispatcher("/userLogin.html").include(request, response);
    		return;
    	}
    	
    	if(!Helper.isValidEmail(email)) {
    		out.println(errorMessage);
    		request.getRequestDispatcher("/userLogin.html").include(request, response);
    		return;
    	}
    	
    	if(!Helper.emailAlreadyRegistered(email, request, response)) {
    		out.println(errorMessage);
    		request.getRequestDispatcher("/userLogin.html").include(request, response);
    		return;
    	}
    	
    	try {
    		if(!Helper.checkPassword(email, password)) {
    			out.println(errorMessage);
        		request.getRequestDispatcher("/userLogin.html").include(request, response);
        		return;
        	}

    		
    	}
    	catch(SQLException e) {
    		out.println(errorMessage);
    	}
    	
    	
    	
    	String name = "";
    	try {
    		name = Helper.getUserName(email);
    	}
    	catch (SQLException e){
    		e.printStackTrace();
    	}
    	
    	name = name.replace(' ', '=');
    	
    	Cookie ck = new Cookie("ck_name", name);
    	
    	ck.setMaxAge(60*60);
    	response.addCookie(ck);
    	Cookie cook = new Cookie("ck_email", email);
    	cook.setMaxAge(60*60);
    	response.addCookie(cook);
    	
    	response.setContentType("text/html");
    	
    	response.sendRedirect("index.jsp");
    	
    	
        //TODO
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     * response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
