#!/bin/bash

ssh stotchbe@192.168.1.30 "sudo chmod o+w /usr/local/bin"
scp cat/s21_cat stotchbe@192.168.1.30:/usr/local/bin 
scp grep/s21_grep stotchbe@192.168.1.30:/usr/local/bin 
ssh stotchbe@192.168.1.30 ls /usr/local/bin
 
