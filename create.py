import random

fp=open("names.txt","r")
fp1=open("file.txt","a")
t=fp.readline();
c=0
offence=["murdrer","robbery","kidnapping","Manslaughter","Larceny","assault","Extortion","High treason"]
prison=["Cellular Jail, Port Blair","Madras Central Prison, Chennai","Bankipur Central Jail, Patna","Freedom Park, Bangalore","Musheerabad Jail, Hyderabad","Viper Island, Andaman Islands","Central Jail, Ahmedabad, Gujarat","Ross Island Penal Colony, Port Blair"]



region=["Awadh","Surat","Dhundhar","Garhwal","Bagar","Godwar","Marwar","Majha","Purba Ghat","Vajjabhumi","Nagar Haveli DNH","Minicoy Island","Chera Nadu","Onattukara","Puducherry","Charotar","Kathiawar","Khandesh"]
while(c<=1000):
        c+=1
        l=t.split(" ")
        name=l[0];
        j=str(random.randint(1,29))
        k=str(random.randint(1,29))
        if (len(j)==1):
                aday="0"+j
        else:
                aday=j
        if (len(k)==1):
                rday="0"+k
        else:
                rday=k
        f=str(random.randint(1,12))
        g=str(random.randint(1,12))
        if (len(f)==1):
                am="0"+f
        else:
                am=f
        if (len(g)==1):
                rm="0"+g
        else:
                rm=g
        ayear=random.randint(1990,2016)
        ryear=random.randint(ayear,ayear+25)

        g=c%(len(region)-1)
        r=c%(len(offence)-1)
        p=c%(len(prison)-1)
        fp1.write(str(c)+"#"+name+"#"+offence[r]+"#"+region[g]+"#"+prison[p]+"#"+aday+"/"+am+"/"+str(ayear)+"#"+rday+"/"+rm+"/"+str(ryear)+"\n")
        t=fp.readline()
fp.close()
fp1.close()
