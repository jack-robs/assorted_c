#!/bin/bash
# The line above makes your script executable.
# You should write your tutorial in here.
# Include comments inline with your script explaining what is going on.

# This script will search for DNS records given common website prefixes, such as
# www, ftp, mail, proxy, router, etc.

# Why: find IP addresses for these DNS records (these websites and sub-nets, i.e. www.corp.com, mail.corp.com, etc.)
# This enables further passive/active recon methods during a pentest, or, conversely, reminds a friendly
# sysadmin/network engineer what the various IPs are, vs. what his documentation shows.
# This uses many great bash commands:
# 1) echo and > and >> (write and append) 'read' input into, and appended to, a file you create at time of read
# 2) $(cat file.txt), which in this case enables a for loop to loop over the 
# contents of the file, line by line
# 3) for var in $(cat *.txt); do XYZ; done: how to loop over contents of a file and perform
# a command on them
# 4) host, a common pre-installed utility for DNS lookup
# 4) grep, a text searching utility that will 'isolate' lines of text
# that matches a pattern we want.

# What is DNS lookup?
# DNS: how a computer matches a domain name, www.mydomain.com, to an IP address, 127.000.00.000

# We will use google.com for this example

# How to think about this:
# GET RAW INPUT
# CLEAN RAW INPUT
# DO SOMETHING ELSE WITH THE CLEAN INPUT

# (PART 1: GET RAW INPUT)
# FIRST: build a file with echo and write/append (> and >>)
echo www > prefix.txt
echo ftp >> prefix.txt
echo mail >> prefix.txt
echo owa >> prefix.txt
echo proxy >> prefix.txt
echo router >> prefix.txt

#Want more options, add these, and/or google 'DNS forward lookup wordlist'
# Source for these:     https://github.com/huggablehacker/forward-dns-lookup/blob/master/list.txt#L17

#firewall
#mx
#pop3
#www3
#imap
#www1
#sftp
#vpn
#siem
#......etc
#

# FYI, our prefix.txt looks like this right now:

#www
#ftp
#mail
#owa
#proxy
#router


# SECOND: We want a 'landing' file for STEP THREE's results, so we'll make an empty one with 'touch'
touch hostraw.txt

# THIRD: for loop over that file:
# What's going on here:
# ip is the variable, like 'for i in range(len(list))' in python
# $(cat prefix.txt) essentially reads the prefix.txt file into the for loop
# for ip will loop line by line, at each newline, and do something with that ip variable
# first loop: ip is 'www'. second loop: ip is 'ftp'. and so on.
# do says 'what to do with the ip variable.' In this case, we concatenate our variable onto our base domain, google.com
# this allows us to rapidly search: host www.google.com. host proxy.google.com. host router.google.com
# In essence: given a huge list of subdomain prexies (www, router, etc), we can rapidly query all possible IPs associated with those
# subdomains. Very cool!
# We are appending the result of each host check into a 'raw input' file, hostraw.txt. I often name these files Xraw.txt to indicate
# the input is 'raw' form, i.e. unformatted largely. 
# `done` ends the loop
for ip in $(cat prefix.txt); do host $ip.google.com >> hostraw.txt; done

# What does this create?
#In hostraw.txt:

#www.google.com has address 172.217.10.132
#www.google.com has IPv6 address 2607:f8b0:4006:812::2004
#Host ftp.google.com not found: 3(NXDOMAIN)
#mail.google.com is an alias for googlemail.l.google.com.
#googlemail.l.google.com has address 172.217.10.101
#googlemail.l.google.com has IPv6 address 2607:f8b0:4006:811::2005
#Host owa.google.com not found: 3(NXDOMAIN)
#Host proxy.google.com not found: 3(NXDOMAIN)
#Host router.google.com not found: 3(NXDOMAIN)


# Now, thinking cap, what is going on here:
# 'successful' DNS records found have the keyword 'has'
# 'failed' lookups, i.e. not found, have the keyword 'not'
# This appears to be consistent across the output in hostraw.txt.
# This may not always be the case in bash-ing like this. The philosophy of the next few steps may create incosistent results, i.e. our final goal,
# a clean list of just 'IPs', might be a little 'messy'. It's helpful to eyeball the various .txt's you create as you create
# the script, in order to make sure your 'cleanup' operations work well. There are usually a few different common tools, like host
# that do essentially the same thing, but the output (location of commas, etc.), may vary a bit.

# TLDR: while building this, check the .txt's you create for unexpected cleaning errors.

#(PART 2: CLEAN RAW INPUT)
# We're going to grep results to find successful subdomains found
# many bash tools (appear) to structure their output to make this possible, i.e.
# 'has,' when used to say a domain was found, will not also be used to indicate a domain was not found, like 'has not'

# grep needs a file to read. An easy way to do this is cat the file, and 'pipe' into the grep command.
# I like to think of piping as similar to providing arguments parameters in a python function. Example:

#bash with piping:
#cat file.txt | grep "dog"


#is conceptually similar to this python pseudo code:

# write function that needs a file, and a thing to grep
#def grep(file, grepThis)
#    ....

# piping will pass in the "file" part of the argument
#grep(file.txt)


# This reads the hostraw.txt, looks for successful IPs, and then puts those into a file with just them, justHas.txt
# It's nice to have semi-cleaned raw input like this, in case you want to do something else to just successful raw results later.
cat hostraw.txt | grep "has" > justHas.txt

# Now, we're going to 'cut', to just get an IP address.
# look at the following
# www.google.com has address 172.217.10.132
# is there a delimter (a space, a comma, etc) that allows one to isolate the IP address? Yes, spaces. 
# www.google.com is the 'first field', has is the 'second field', address is the 'third field', and '172..' is the 4th.
# There is a way to access these fields specifically, and output it a new file, with 'cut'.

# try running this on your own
# cat justHas.txt | cut -d" " -f4,5
# It outputs the following:

#cat justHas.txt | cut -d" " -f4,5
#172.217.10.132
#address 2607:f8b0:4006:812::2004
#172.217.10.101
#address 2607:f8b0:4006:811::2005

# What does this indicate? Host puts out slightly different reults for IPv4 (172..) results, vs. IPv6 (2607....)
# That's ok actually, we'll use it to create two output files. Clean IPv4, and clean IPv6. 
# I mention this to reference what I said before, it's helpful to read the files you create in stages and see how the output looks

# creates a list of just IP v4 IPs
cat justHas.txt | cut -d" " -f4 | grep "172" > cleanip4.txt


#cat cleanip4.txt: 
#172.217.10.132
#172.217.10.101'

# creates a list/file of just IP v6 IPs:
cat justHas.txt | cut -d" " -f5 | grep "2607" > cleanIP6.txt


#cat cleanIP6.txt 
#2607:f8b0:4006:812::2004
#2607:f8b0:4006:811::2005'

# So, now, we have a list of the IPs (two types, V4 and V6), associated with googles subdomains, that we could find on first pass.
# First pass? Host is sort of a 'first pass' type of efforts. It's an easy command to run, won't flood a network, won't set off 
# security alarms, etc.

# This ends out effective tutorial, with these two files:

#cat cleanIP6.txt:
#2607:f8b0:4006:812::2004
#2607:f8b0:4006:811::2005'

#And

#cat cleanip4.txt 
#172.217.10.132
#172.217.10.101'

# What can we do with these?
# DO THESE WITH PERMISSION FROM THE NETWORK ADMIN

# this will scan each IP for the software running and open ports. This can be helpful to determine if software you think
# is open to the internet, is in fact open. Or, inverse, you want it close dbut it's open.
# for ip in $(cat cleanip4.txt); do nmap -sN ip; done;
