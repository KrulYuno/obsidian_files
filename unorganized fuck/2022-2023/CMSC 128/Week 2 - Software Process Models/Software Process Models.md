# Process Models
Check generic process framework [here](Software%20Engineering%20and%20Processes.md#The%20Process%20Framework)


## Waterfall Model
![[Pasted image 20220927084503.png]]
- a linear process flow
- sequential
- plan-driven process
- must plan and schedule all activies before starting
- each activities are represented as a separate phase arranged in linear order
- classic life cycle
	- illustrates the phases of software development
	- oldest process model being followed by industries even to this day


## Phases
1. Requirements / Requirements Analysis / Communication
2. System Design / Planning
3. Implementation / Modelling
4. Testing / Construction
5. Deployment
6. Maintenance

```diff
+ simple
+ easy to understand, use, and manage
+ activities are completed one at a time
+ rigid structure, very well understood requirements and unlikely to radical change
+ clearly defined stages
- no working software is produced until the last phase
- inflexible, cannot adapt to changes
- high risk
- poor model for large and ongoing project
- not designed for object-oriented programming
```


# V-Model
![[Pasted image 20220927091832.png]]
- **Verification** and **Validation** model
- variation/extension of [waterfall model](#Waterfall%20Model)
- all requirements are gathered from the start and cannot be changed
- for every phase in development cycle, there is an **associated testing phase**
- depicts the relationship of quality asssurance actions
- provides a way of visualizing how verification and validation actions are applied to earlier engineering work
`The corresponding testing phase of the development phase is planned in parallel, as you can see above.`


## Phases
1. Requirement Analysis  --> System/Acceptance Testing
2. High Level Design       --> Integration Testing
3. Low Level Design        --> Unit Testing
4. Coding

```diff
+ highly disciplined, easy to understand, and makes project management easier
+ good choice for software where downtimes and failures are unacceptable
- not good for complex project or projects that have unclear or changing requirements
```

# Incremental Process Model
![[Pasted image 20220927095214.png]]
- divide the system's functionality into **small increments** that are delivered oen after the other in quick section
- initial increments are implemented as the most important functionality
	- 1st increment: `core product`
- subsequent increments expand on the previous ones until everything has been updated and implemented
	- process' activities are interwoven by feedback
- method of software development where the model is designed, implemented and tested incrementally (a little more is added each time) until the product is finished
- involves both in **development** and **maintenance**
	- product is finished when all requirements are satisfied
- this model combines the elements of [waterfall model](#Waterfall%20Model) with the iterative philosophy of [prototyping](#Prototyping) (combines linear and parallel process flows)

```diff
+ useful to mitigate technical risks
+ applicable to projects who need to be delivered quickly and whose primary or core functionalities are know and can be articulated
+ applicable to well-staffed project teams 
- 
```



*Evolutionary process flows begins here*
# Prototyping
![[Pasted image 20221001190505.png]]
- built to be throways
- used for acquiring feedback
- iterates across all processes quickly for feedback
```diff
+ appropriate for projects when clients cannot fully specify the requirements of the software
+ can be used to build or clarify user requirements
- stakeholders may think that the prototype is the final software
- stakehoders may think that the software can be completed earlier than planned
- prone to programming blunders
```
# Spiral Model
![[Pasted image 20220927105124.png]]
- risk driven iterative software process model
	- introduced for dealing the shortcomings of the waterfall model
- steps are not activities 
	- they are **phases** for addressing problem with greatest risk of causing failure
- can be used for *unclear needs* or projects still in research and development

Phases each cycle:
1.  Address the highest-risk problem and determine the objective and alternate solutions
2.  Evaluate the alternatives and identify the risks involved and possible solutions
3.  Develop a solution and verify if it???s acceptable
4.  Plan for the next cycle


```diff
+ great for managing uncertainty
- difficult to have stable documentation
```

----
Check references [here](REFERENCES.md#Software%20Process%20Models).