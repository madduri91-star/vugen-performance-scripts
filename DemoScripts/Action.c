Action()
{
	
    /* ===============================
       1?? Open Home Page
    =============================== */

    lr_start_transaction("01_Open_HomePage");

    web_reg_find("Text=Welcome to the Simple Travel Agency!",
                 "SaveCount=HomePageCheck",
                 LAST);

    web_url("Open_HomePage",
        "URL=https://blazedemo.com/",
        "Resource=0",
        "RecContentType=text/html",
        "Mode=HTTP",
        LAST);

    if (atoi(lr_eval_string("{HomePageCheck}")) > 0)
        lr_end_transaction("01_Open_HomePage", LR_PASS);
    else
        lr_end_transaction("01_Open_HomePage", LR_FAIL);

    lr_think_time(3);


    /* ===============================
       2?? Find Flights (Parameterized)
    =============================== */

    lr_start_transaction("02_Find_Flights");

    web_reg_find("Text=Flights from",
                 "SaveCount=FindFlightCheck",
                 LAST);

    web_submit_data("Find_Flights",
        "Action=https://blazedemo.com/reserve.php",
        "Method=POST",
        "RecContentType=text/html",
        "Mode=HTTP",
        ITEMDATA,
        "Name=fromPort", "Value=Paris", ENDITEM,
        "Name=toPort", "Value=London", ENDITEM,
        LAST);

    if (atoi(lr_eval_string("{FindFlightCheck}")) > 0)
        lr_end_transaction("02_Find_Flights", LR_PASS);
    else
        lr_end_transaction("02_Find_Flights", LR_FAIL);

    lr_think_time(4);


    /* ===============================
       3?? Correlation – Capture dynamic flight value
    =============================== */

//    web_reg_save_param("FlightValue",
//        "LB=name=\"flight\" value=\"",
//        "RB=\"",
//        "Ord=1",
//        LAST);

    lr_start_transaction("03_Choose_Flight");

   web_submit_data("Choose_Flight",
        "Action=https://blazedemo.com/purchase.php",
        "Method=POST",
        "RecContentType=text/html",
        "Mode=HTTP",
        ITEMDATA,
        "Name=flight", "Value=43", ENDITEM,
        LAST);

    lr_end_transaction("03_Choose_Flight", LR_AUTO);

    lr_think_time(3);


    /* ===============================
       4?? Purchase Ticket (Parameterized)
    =============================== */

    web_reg_find("Text=Thank you for your purchase today!",
                 "SaveCount=PurchaseCheck",
                 LAST);

    lr_start_transaction("04_Purchase_Ticket");

    web_submit_data("Purchase_Ticket",
        "Action=https://blazedemo.com/confirmation.php",
        "Method=POST",
        "RecContentType=text/html",
        "Mode=HTTP",
        ITEMDATA,
        "Name=inputName", "Value=Anil Test", ENDITEM,
        "Name=address", "Value=Hyderabad", ENDITEM,
        "Name=city", "Value=Hyderabad", ENDITEM,
        "Name=state", "Value=TS", ENDITEM,
        "Name=zipCode", "Value=500001", ENDITEM,
        "Name=creditCardNumber", "Value=4111111111111111", ENDITEM,
        "Name=creditCardMonth", "Value=12", ENDITEM,
        "Name=creditCardYear", "Value=2028", ENDITEM,
        "Name=nameOnCard", "Value=Anil Test", ENDITEM,
        LAST);

    if (atoi(lr_eval_string("{PurchaseCheck}")) > 0)
        lr_end_transaction("04_Purchase_Ticket", LR_PASS);
    else
        lr_end_transaction("04_Purchase_Ticket", LR_FAIL);
	
	return 0;
}
