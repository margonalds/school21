# Integration of IT systems

Summary:
In this project, you will learn about IT systems integration, the major integration styles, and the work of a systems analyst in integration.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Preamble](#11)
2. [Chapter II](#chapter-ii) \
   2.1. [General Rules](#21)
3. [Chapter III](#chapter-iii) \
   3.1. [General Concepts](#31) \
   3.2. [Need for Integration](#32) \
   3.3. [Integration Criteria](#33) \
   3.4. [Integration Styles](#34)
4. [Chapter IV](#chapter-iv) \
   4.1. [Task 2. Delivery of Orders](#41) \
   4.2. [Task 3. Warehouse Storage)](#42)
5. [Chapter V](#chapter-v) \
   5.1. [Exercise 00 — Data Flows Identification](#51) \
   5.2. [Exercise 01 — Master Systems Identification](#52) \
   5.3. [Exercise 02 — Recipient Systems Identification](#53) \
   5.4. [Exercise 03 — Data Dictionary](#53) \
   5.5. [Exercise 04 — Integration Scenarios Description](#55) \
   5.6. [Exercise 05 — Define Volume and Quantity Requirements for Data Flows](#56) \
   5.7. [Exercise 06 — Determining Frequency and Timing for Data Flows](#57)

## Instructions 

How to learn at “School 21”:

- Here, you’ll find a unique learning experience with a lot of freedom. You’re given a task and left to find your own way to solve it, using whatever resources work best for you — whether that’s the Internet or AI tools like GigaChat. Just be mindful of information quality: verify, think critically, analyze, and compare.
- Peer-to-peer (P2P) learning is the exchange of knowledge and experience with peers, where everyone acts as both mentor and student. This approach allows you to gain a deeper understanding of the material by learning from one another.
- Feel free to ask for help: around you are peers who are also navigating this path for the first time. Share your own experience and ideas with others.  Join Rocket.Chat to stay updated with the latest community announcements. 
- Your learning is meaningless if you just copy someone else’s solutions. When receiving help from others, always make sure you fully understand the “why”, “how”, and “purpose” behind the solution. Don’t be afraid to make mistakes. 
- Does the task seem impossible? Take a break, get some fresh air and clear your mind — this has helped many people. Maybe after that, the solution will come to you naturally.
- The learning process is just as important as the result. It’s not just about completing the task — it’s about understanding HOW to solve it.

## Chapter I <div id="chapter-i"></div>

![Illustration](misc/images/IMG_1816.jpg)

### Preamble <div id="11"></div>

Integration is the process of establishing connections between information systems to create a single information space and support end-to-end business processes. Integration occurs wherever the same or similar data is used, or where information or control actions are transferred from one system to another. Depending on your capabilities and needs, integration can be accomplished in a number of ways. To understand which integration method is best, you should formulate your integration requirements. In this project, you will look at data integration. 

### Literature

1. [Enterprise Integration Patterns | by Gregor Hohpe, Bobby Woolf](https://www.litres.ru/bobbi-vulf/shablony-integracii-korporativnyh-prilozheniy-48637947/). /Chapters 1-2. 
2. [Application and integration architecture: a guide to the basic concepts in simple words](https://habr.com/ru/company/itq_group/blog/705598/).
3. [Integration of information systems](https://habr.com/ru/post/117468/).
4. [Fear integration — don't go into analytics / habr.com](https://habr.com/ru/companies/maxilect/articles/592533/).

## Chapter II <div id="chapter-ii"></div>

### General Rules <div id="21"></div>

Before starting, clone the project from GitLab into a repository with the same name.

1. Along the way, you may feel a sense of uncertainty and a severe lack of information: that's OK. Remember, the information in the repository and on Google is always with you. So are your peers and Rocket.Chat. Communicate. Search. Use common sense. Don't be afraid to make mistakes.
2. Pay attention to sources of information. Check. Think. Analyse. Compare. 
3. Look at the text of each assignment. Read it several times. 
4. Read the examples carefully. There may be something in them that is not explicitly stated in the task itself.
5. You may find inconsistencies where something new in the terms of the task or examples conflicts with something you already know. If you come across such an inconsistency, try to work it out. If not, write it down as an open question and find out as you work. Do not leave open questions unanswered. 
6. If a task seems confusing or impossible, it only seems that way. Try to break it down. It is likely that some parts will become clear. 
7. There will be several tasks. Those marked with an asterisk (\*) are for the more meticulous students. These tasks are more difficult and are not compulsory. But doing them will give you extra experience and knowledge.
8. Don't try to fool the system or the people around you. You will fool yourself first.
9. Got a question? Ask your neighbour to the right. If that doesn't help, ask your neighbour on the left.
10. When you use help, you should always understand why and how. Otherwise the help is useless.
11. Always push only to the _develop_ branch! The master branch will be ignored. Work in the _src_ directory.
12. There should be no files in your directory other than those specified in the tasks.

## Chapter III <div id="chapter-iii"></div>

### 1. General Concepts <div id="31"></div>

For a general understanding of the integration process, it is useful to know one of the ways of data transfer (in client-server architecture), which is described in the simplest way in the article [Client-server architecture in pictures](https://habr.com/ru/post/495698/). 

Development of integration includes the following steps

1. Identifying the need for integration (functional requirements, what needs to be transferred). 
2. Identify the quality attributes of the integration (non-functional requirements, how to transfer).
3. Select the interoperating systems (master system or receiver system).
4. Define the requirements for converting classes of one system to classes of another.
5. Choose an integration solution (integration styles and scenarios).
6. Identify integration logging requirements.
7. Error description.
8. Develop integration calls.
9. Test the integration.

The system analyst participates in steps 1-7. Also, after studying additional material, can participate in steps 8, 9.  In this project, you will review the system analyst's involvement in data integration in steps 1, 2, 3. And in the future projects in steps 4-7. 

### 2. Need for Integration <div id="32"></div>

The need for integration of certain data is determined during the analysis and identification of business requirements, stakeholder requirements, and functional requirements for the system. For example, to pay with a bank card at the store, it is necessary to get information from the bank that there is money on the current card to pay for the purchase. Checking the context diagram, business process diagrams, US, UC of the whole task you will be able to write out the list of data flows and their purpose. Later you will need to describe the structure and formats of data and compare them in different systems (mapping).  This is the job of a systems analyst. 

### 3. Integration Criteria <div id="33"></div>

Information about the amount of money available on a bank card must be received by the store fairly quickly, and it is unrealistic to wait several hours for a response at the cash register. But large reports to a higher organization, sent once every one to three months, containing hundreds and thousands of indicators, are quite acceptable. Or the information about the shipment of the composition with semi-finished products to the enterprise, where these semi-finished products will be incorporated into the product for the end user — it also needs to be transferred as quickly as possible, but it is not as critical as the information about the payment. Let's consider some of the most applicable criteria for choosing the type (style) of integration.

1. **Amounts and Volumes of Data**

The difference in data transfer volumes is well illustrated by the two examples above. For example, you can calculate the number of messages and their approximate average and maximum size per month. At the same time, the data may be approximate, not exact. And there may be a solution where not the full information is transferred, but a variation, a delta.

2. **Timing and Frequency of Transmission**

How often requests are sent/received, whether there are periods when the integration flow is absent or significantly reduced. When the flow is maximum (peak period). How the information should be received, e.g. all information for yesterday's day should reach the bank by 10:00 the next day (operational day).

3. **Data formats and Schema, Business Logic** 

The parties involved in the data exchange must agree on what formats (data types, dimensionality, binding), what schema (in what order and with what nesting) the data will be transferred, and how often the schema and formats will be changed. And sometimes complex business logic, conditions, and tests are applied during the formation of the transmitted data or after it is received, during parsing. This should also be considered when choosing an integration method.

4. **Timeliness of Data Transfer, Synchrony and Asynchrony**

It is often necessary to get a response quickly enough, for example, to pay for a purchase. In this case, after sending a request, the system waits for a response from the other system without interrupting other actions. This type of communication is called synchronous, as opposed to asynchronous, where the system sends data or a request and does not expect an immediate response. The response may come later, and that is fine with the source system. However, with asynchronous transmission, before a response is received, it may be necessary to send a new transmission with updated data, for example, in the case of a report transmission to correct errors found in previously sent reports.

5. **Mapping**

Often data is stored in different structures and formats in interacting systems. Mapping is used to transfer data from one structure to another. Mapping is done by a system analyst.

### 4. Integration Styles <div id="34"></div>

The need to obtain data is closely related to the conditions and constraints that should be considered when selecting integration methods (styles). 

The main styles of integration:

1. **Common Database**

Two or more systems access the same information stored in a single database. Currently, this is often implemented as a single enterprise data repository. It should be noted that there is sometimes a delay in placing data from different systems into the repository.

Advantages:

- Consistency of stored information, eliminating different interpretations of data by different systems.
- Integrated systems use a common language of exchange with the database (e.g. SQL), even if they are developed on different technologies;
- Possibility of frequent data exchange.

Disadvantages:

- Difficulty in developing a common database schema.
- Possibility of performance degradation or data locking as the number of data accesses increases.
- Non-encapsulated data. Changing the data schema of one application can affect other applications, making it difficult to support integrated applications and preventing the implementation of new business functionality.

2. **File Exchange**

One system (or multiple systems) places files in a predetermined location, and another system (or multiple systems) reads them from there. A variation is file transfer by mail or messenger. Because of its ease of implementation, it is convenient for one-time integrations. 

Advantages:

- Weak coupling of the integrated applications. No internal implementation information needed. Main task is format conversion (if needed).
- File transfer is easy to implement.

Disadvantages:

- Low exchange rate and possibility of unsynchronization. Sometimes a file sent later may arrive at the receiving system earlier than the previous file, which can disrupt the business logic.
- As the load increases, processing a large number of files can overload the system and cause unsynchronization.
- Messages about delivery and validation of received information should be considered when designing a business process.
- Control over file name uniqueness and deletion of old files is necessary.

The most common exchange file formats are:

- [CSV](https://ru.wikipedia.org/wiki/CSV)
- [XML](https://ru.wikipedia.org/wiki/XML)
- [JSON](https://ru.wikipedia.org/wiki/JSON)
- [YAML](https://ru.wikipedia.org/wiki/YAML)

Links to format specifications and study materials can be found in the Literature section.

3. **Messaging**

Allows you to organize messaging for fast, instantaneous, reliable, and asynchronous transmission of variable-format data. One system sends a message to another system, and the other system sends the requested information.

Advantages:

- Allows for frequent exchange, which reduces the chance of data mismatch.
- Allows for asynchronous exchange. Information transfer does not require simultaneous availability of sender and receiver.
- Provides weak coupling. Messages can be transformed during transmission without notifying the sender or receiver.
- Different delivery methods can be used: routing to one or a group, broadcasting, etc.

Disadvantages:

- Does not allow complete elimination of latency in information delivery.
- Difficult to test and debug.
- Requires creation of mechanisms for message conversion in case of data schema mismatch.

4. **Remote Procedure Call**

One system does not transfer data to another system, but causes its procedures to be executed.

Advantages:

- Allows to implement integration of application functionality.
- It is possible to change the data format of a single application without affecting other applications. Each application independently ensures the integrity of its data.
- Allows providing multiple interfaces for the same data from different perspectives.
- Provides additional features such as transaction support.

Disadvantages:

- There can be a high degree of application coupling.
- Failure of one application can cause failure of all applications that rely on its functionality.

The most common technologies currently used to implement RPC are:

- [SOAP](https://ru.wikipedia.org/wiki/SOAP)
- [REST](https://ru.wikipedia.org/wiki/REST)

A more detailed description of integration styles can be found in the book by Gregor Hohpe, Bobby Woolf [Enterprise Integration Patterns](https://www.enterpriseintegrationpatterns.com/patterns/messaging/FileTransferIntegration.html), chapters 1,2. Each integration style has both certain positive qualities and some limitations that should be considered when choosing a style and designing a solution.

The choice of integration style is made by the architect. But he makes it on the basis of information about the conditions and limitations of data transfer (integration criteria). And this information is collected and described by the analyst.

## Chapter IV <div id="chapter-iv"></div>

### Description of tasks

### Task 2. Delivery of orders <div id="41"></div>

During the lockdown, many grocery stores and food companies dramatically increased their online sales and the need for quick delivery of small quantities to individual customers increased. 

A group of students got together and decided to create a delivery service startup. The idea is to quickly receive information about orders, pickup location and time, delivery location, desired delivery dates, and distribute this information to couriers who will pick up the order at the pickup location and deliver it to the delivery location. They decided to develop an online system where orders could be collected and quickly sorted for delivery by couriers.

The first step was to collect orders from stores and caterers in any way possible and have the operator enter them into the system in a consistent format, as well as developing a mobile application for the courier. The courier should be able to view order information, select an order from those available, book it, pick it up at the collection point and deliver it to the customer. The result of the courier's actions should be immediately reflected in the system via a mobile application. The system should also include a dispatcher who controls the couriers and reassigns orders if necessary. Information on received orders should be sent to the accounting department (to another IT system) to calculate delivery charges with order suppliers. Order delivery information should also be sent to the accounting department to calculate payment to couriers. Accrued payment should be transferred to the system and displayed in the courier's personal account. And there should also be an administrator's workstation, where couriers are registered and access rights are assigned to all of them.

### Task 3. Warehouse Storage <div id="42"></div>

A logistics company engaged in cargo transportation has decided to expand its business and organize the lease of warehouses for temporary or permanent storage of things and goods for individuals and legal entities. It is planned to rent and build warehouses in different parts of the city. The first: "Kamorka" — a system in the company, which provides accounting of rent of individual boxes of size from 3 to 15 square meters by individuals for storage of personal belongings, furniture, sports equipment.

The management of the company (customer) decided to introduce a centralized rental accounting of boxes, occupied and vacant, payment, access control and cleaning after vacating. Access to the warehouse itself is provided by a third party security company, which needs to be informed about new or dropped customers. The security company issues an electronic pass to the storage area for the specified period of time, extends or stops the validity of the pass in case of renewal or early termination of the lease agreement. The boxes are cleaned by the cleaning company after their use and before they are handed over to a new client. The purpose of the system implementation is to reduce manual work and personnel costs, reduce overhead costs, optimize box filling (minimize idle time of empty boxes), operational accounting of cash flow.

The client (individual) contacts the logistics company and through the manager concludes a contract for renting a box of the required size. To do this, the manager must have up-to-date information about available and soon-to-be vacant boxes. The client does not interact directly with the system, all information is provided by the manager. When the contract expires, the manager warns the client of the need to renew or terminate the contract and vacate the box. The manager is also responsible for organizing the cleaning of the boxes by a third-party company after they are vacated, as well as for organizing the client's access to the storage area, which is provided by a security company. After signing the contract, the manager informs the storekeeper about the allocation of a particular vacant box. The storekeeper checks the availability of the box (release of the previous tenant's belongings and cleaning), hands over the key to the box to the client, controls the release and cleaning of the boxes.

The team has an accountant. He/she calculates payments and controls income, payments to clients, payments for cleaning of boxes and security of the warehouse. The accountant receives information about new contracts and their changes from the manager. The payment for the cleaning of the boxes is calculated monthly on the basis of the area, the payment for the security — also monthly on the basis of the number of clients of the logistics company.

## Chapter V <div id="chapter-v"></div>

### Exercise 00 — Data Flows Identification <div id="51"></div>

For Task 2, identify at least 6 data flows. 

1. Write out the data flows required for our system:
   1. name of the data flow;
   2. the purpose (goal) of the data flow;
   3. the direction of the data flow (in or out of the system).
2. Present in tabular form.

**Scale from 1 to 5**

### Exercise 01 — Master Systems Identification <div id="52"></div>

For Task 2, identify the masters for the incoming data. 

1. In the table created in ex.00, for each incoming data flow, add the possible variants of systems in the environment suitable for receiving the data. 
2. For each incoming flow, select and specify a master system.
3. Briefly rationalize the selection of the master system (specify the purpose of obtaining the data).
4. Present the results in tabular form.

**Scale from 1 to 5**

### Exercise 02 — Recipient Systems Identification <div id="53"></div>

For Task 2, identify the recipient systems for the outgoing data. 

1. In the table created in ex.00, for each outgoing data flow, add the possible variants of systems in the environment that potentially require data. 
2. For each outgoing flow, select and specify the recipient system(s).
3. Briefly rationalize the selection of the recipient system(s) (specify the purpose for sending the data).
4. Check that the destination system and master system match for data flows containing linked data. 
5. Present the results in tabular form.

**Scale from 1 to 5**

### Exercise 03 — Data Dictionary <div id="54"></div>

Develop a data dictionary for each data flow of Task 2.

1. Specify the name of the flow, purpose, and direction.
2. Specify blocks, nesting, mandatory blocks.
3. Describe attributes:
   1. attribute name;
   2. data type;
   3. length (for text);
   4. whether it is neccesary or not;
   5. constraints or conditions. 
4. Present the results in tabular form, with heading according to item 1.

**Scale from 1 to 5**

### Exercise 04 — Integration Scenarios Description <div id="55"></div>

For each flow of Task 2, develop an integration scenario in the form of a UC or diagram.

**Scale from 1 to 5**

### Exercise 05 — Define Volume and Quantity Requirements for Data Flows <div id="56"></div>

For each flow of task 2, determine:

1. The average number of messages per unit time;
2. The average size of a single message;
3. Peak load periods;
4. Peak number of messages per unit time;
5. Peak number of messages per unit of time.

**Scale from 1 to 5**

### Exercise 06 — Determining Frequency and Timing for Data Flows <div id="57"></div>

For each flow of task 2, determine:

1. The desired transmission frequency; 
2. The desired delivery time;
3. The maximum and minimum possible transmission frequency;
4. Maximum and minimum possible delivery time.

**Scale from 1 to 5**
