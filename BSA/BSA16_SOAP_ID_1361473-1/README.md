# Integration with SOAP web services

Summary: In this project, you will learn about how web services communicate between IT systems using the SOAP protocol. You will also learn about the advantages and disadvantages of these exchanges. You will learn how to read XML document markup language, which is used to pass messages, and how to use XML document structure descriptions and the WSDL web services description language.

💡 [Tap here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) **to leave your feedback on the project**. It's anonymous and will help our team make your educational experience better. We recommend completing the survey immediately after the project.

## Contents

1. [Chapter I](#chapter-i) \
   1.1. [Preamble](#11)
2. [Chapter II](#chapter-ii) \
   2.1. [General Rules](#21)
3. [Chapter III](#chapter-iii) \
   3.1. [Theory](#31) \
   3.2. [Standards and Basic Concepts](#32) \
   3.3. [Two Approaches to Development: CODE-FIRST и CONTRACT-FIRST](#33) \
   3.4. [Recommendations for Study](#34)
4. [Chapter IV](#chapter-iv) \
   4.1. [Task 4. SOAP Services — Pet Lovers Club](#41)
5. [Chapter V](#chapter-v) \
   5.1. [Exercise 00 — Functions of WSDL First Level Tags](#51) \
   5.2. [Exercise 01 — Methods of `<portType>`](#52) \
   5.3. [Exercise 02 — Section `<schema>`](#53) \
   5.4. [Exercise 03 — Reverse Engineering](#53) \
   5.5. [Exercise 04 — Reverse Engineering, Addition](#55) \
   5.6. [Exercise 05 — Endpoint Definition](#56)

## Instructions 

How to learn at “School 21”:

- Here, you’ll find a unique learning experience with a lot of freedom. You’re given a task and left to find your own way to solve it, using whatever resources work best for you — whether that’s the Internet or AI tools like GigaChat. Just be mindful of information quality: verify, think critically, analyze, and compare.
- Peer-to-peer (P2P) learning is the exchange of knowledge and experience with peers, where everyone acts as both mentor and student. This approach allows you to gain a deeper understanding of the material by learning from one another.
- Feel free to ask for help: around you are peers who are also navigating this path for the first time. Share your own experience and ideas with others.  Join Rocket.Chat to stay updated with the latest community announcements. 
- Your learning is meaningless if you just copy someone else’s solutions. When receiving help from others, always make sure you fully understand the “why”, “how”, and “purpose” behind the solution. Don’t be afraid to make mistakes. 
- Does the task seem impossible? Take a break, get some fresh air and clear your mind — this has helped many people. Maybe after that, the solution will come to you naturally.
- The learning process is just as important as the result. It’s not just about completing the task — it’s about understanding HOW to solve it.

## Chapter I <div id="chapter-i"></div>

![Иллюстрация к проекту](misc/images/IMG_1817.jpg)  

### Preamble <div id="11"></div>

There is a common perception that SOAP integration is an outdated, old-fashioned technology. But many large enterprises use SOAP. And not because integration was developed years ago, when RESTful was little known. In fact, the first mention is close in time. The REST architectural style was introduced in [Roy Fielding's](https://ru.wikipedia.org/wiki/%D0%A4%D0%B8%D0%BB%D0%B4%D0%B8%D0%BD%D0%B3,_%D0%A0%D0%BE%D0%B9) thesis in 2000, and SOAP (Simple Object Access Protocol) appeared in 1998.

In fact, different environments are more suited to different technology-driven integration styles.  

### Literature

1. World Wide Web Consortium (W3C) Standards <https://www.w3schools.com/> \
   XML: <https://www.w3schools.com/xml/default.asp> \
   XSD: <https://www.w3schools.com/xml/schema_intro.asp> \
   WSDL: <https://www.w3schools.com/xml/xml_wsdl.asp> \
   SOAP: <https://www.w3schools.com/xml/xml_soap.asp> \
   <https://www.w3.org/TR/2001/NOTE-wsdl-20010315>
2. Ildar Khabibullin. XML Self-Tutorial (Chapter 1 (XML Document Structure), Chapter 3 (Description of Document Structure in XSD Language)).

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

### Theory <div id="31"></div>

SOAP is a protocol for the exchange of structured messages. Unlike the architectural style of REST, SOAP is a standardized protocol. Messages are passed in XML format. The advantages of SOAP include:

- Standardization by the World Wide Web Consortium (W3C), an organization that develops Internet standards. All developers know and understand the rules by which exchange is built. Unlike RESTful integration, which must be negotiated case-by-case.
- Unambiguity of standards. This is another positive difference from RESTful.
- Many programming languages have libraries that support SOAP, which reduces developer work and errors.
- There is support for error handling integration, which also reduces costs and errors.

However, there are disadvantages to consider:

- It requires access to large libraries. Therefore, it does not always make sense to use it on mobile devices because Internet availability is not always perfect.

SOAP technology includes formal descriptions of services and transferred data. Documents of formal descriptions, as well as transmitted messages, are based on XML technologies. Therefore, the study of SOAP should begin with learning the basics of XML technologies.

Formalized description of data and services allows unambiguous interpretation of requirements by different participants of development processes, for example, in different organizations involved in integration of their systems. 

### 1. Standards and Basic Concepts <div id="32"></div>

**XML** is a document markup language. It is used to format transmitted messages and documents that formally describe the structure of messages and services.

**XSD** is an XML document structure description language. It is used to formally describe the structure of transmitted messages and data types.

**WSDL** is a language for describing web services. It describes operations implemented by the service, input/output messages, the address of the service, and so on.

### 2. Two Approaches of Development: CODE-FIRST и CONTRACT-FIRST <div id="33"></div>

The formalized description of data and services allows not only the unambiguous interpretation of requirements by different participants in the development process, but also the automatic generation of program code elements based on documents, or vice versa, the generation of formal documents based on developed program code.

This results in 1) saving labor costs, and 2) ensuring compliance between documents and code.

There are 2 approaches to document and code development:

- CODE-FIRST — code is developed first and documents are generated based on the code;
- CONTRACT-FIRST — program code elements are generated based on completed documents.
  Based on extensive development experience, the following approach is recommended when integrating different systems. For the first system, the development is done according to the native language requirements, then the documents are generated (CODE-FIRST). The documents are then handed over to the developers of the other systems, who generate the code (CONTRACT-FIRST).
  All of the above applies to both Web services development and integration via XML file exchange.

### 3. Recommendations for Study <div id="34"></div>

What to pay attention to in order to avoid common mistakes and misunderstandings.

1. The characters `<, >, &`, quotes are used for XML formatting. Therefore, they cannot be placed in text data and are replaced in a special way. See <https://www.w3schools.com/xml/xml_syntax.asp>, Entity References section. 
2. The XML standard allows a single date and time format. See <https://www.w3schools.com/xml/schema_dtypes_date.asp>, Habibullin p. 64. The well-known date format "dd.mm.yyyyy" and other fantasies are not provided by the standard.
3. Definition of complex types and `<sequence>` tag is a must!
4. Namespaces. See Khabibullin page 81, <https://www.w3schools.com/xml/xml_namespaces.asp>, <https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%BE%D1%81%D1%82%D1%80%D0%B0%D0%BD%D1%81%D1%82%D0%B2%D0%BE_%D0%B8%D0%BC%D1%91%D0%BD_(XML)> — a complicated topic for initial study.
5. WSDL. Data description can be both within a WSDL document (following XSD rules) and in separate XSD documents referenced in WSDL.
6. Note this is for some reason rarely described anywhere. An operation described in WSDL can have only 2 messages, **input** and **output**, as well as a third **fault,** returned by the service in case of an error. See in the standard <https://www.w3.org/TR/2001/NOTE-wsdl-20010315#_porttypes>.

## Chapter IV <div id="chapter-iv"></div>

### Description of tasks

### Task 4. SOAP Services — Pet Lovers Club <div id="41"></div>

The developers of the city N have organized a "Pet Lovers Club" in their environment and decided to create a database of club members and their pets. Two web services using the SOAP protocol were developed to maintain the database. Everyone will write the client software in their favorite programming language or use SoapUI or Postman programs. 

The first web service is intended to maintain (add, correct, read, delete) the list of club members, and the second web service is intended to maintain the list of their pets. The web services are described by two WSDL documents in the files member.wsdl and pet.wsdl.

## Chapter V <div id="chapter-v"></div>

### Exercise 00 — Functions of WSDL First Level Tags <div id="51"></div>

Based on the WSDL document of Task 4:

1. Write out the logical parts of the WSDL document (first level tags).
2. State the function of each logical part except for the `<binding>` tag.
3. Specify with a single phrase.
4. Present in tabular form.

### Exercise 01 — Methods of `<portType>` <div id="52"></div>

Based on the `<portType>` section of the WSDL documents of Task 4:

1. Write out the operations (methods) of the services of the `<portType>` section. 
2. Specify the function of operations.
3. Identify the function of operations by operation name.
4. Present the result in tabular form.

### Exercise 02 — Section `<schema>` <div id="53"></div>

1. Based on the `<schema>` section of WSDL documents, determine:
   1. The function of the `<element>`;
   2. function of the type attribute of the `<element>` element;
   3. function of the `<complexType>` element;
   4. function of minOccurs attribute;
   5. function of maxOccurs attribute.
2. Specify:
   1. What is the meaning of the `<sequence>` element?
   2. What does it mean if minOccurs or maxOccurs is not specified?
   3. What does this mean? maxOccurs="unbounded" 
   4. How to understand if an element must necessarily be present in an XML message?
3. Describe with one phrase.
4. Present the results in tabular form.

### Exercise 03 — Reverse Engineering <div id="54"></div>

For Task 4, use the available WSDL to perform reverse engineering, i.e. describe the development requirements. 

Explanation: Element "kind" — type of animal: cat/dog/python/hamster.

1. Describe the input and output message formats for the following operations:
   1. addMember,
   2. addPet,
   3. updatePet,
   4. getAllMembers.
2. Specify for input and output:
   1. number,
   2. transaction name,
   3. function,
   4. type (only simple types: string/int/decimal/string/integer/number, do not specify complex types),
   5. array (if array — specify "yes", otherwise empty),
   6. mandatory (if mandatory — specify "yes", otherwise empty),
   7. note.
3. Present the results in tabular form.

### Exercise 04 — Reverse Engineering, Addition <div id="55"></div>

In addition to Exercise 04 for Task 4, specify:

1. How the output messages of getAllMembers and getMemberByName operations differ. 
2. Specify the result in one phrase.

### Exercise 05 — Endpoint Definition <div id="56"></div>

For Task 4 on WSDL documents: 

1. Define endpoint (URL, service address):
   1. For Web service member;
   2. For Web service pet.
2. Present the results in tabular form.
