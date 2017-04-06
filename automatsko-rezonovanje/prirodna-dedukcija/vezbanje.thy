theory vezbanje
imports Main

begin

thm notI           (* Uvodjenje negacije *)
thm notE           (* Eliminacija negacije *)
thm conjI          (* Uvodjenje konjunkcije  *)
thm conjunct1      (* Eliminacija konjunkcije po prvom konjuktu *)
thm conjunct2      (* Eliminacija konjunkcije po drugom konjuktu *)
thm conjE          (* Eliminacija konjunkcije *)
thm disjI1         (* Uvodjenje disjunkcije po prvom disjunktu *)
thm disjI2         (* Uvodjenje disjunkcije po drugom disjunktu *)
thm disjE          (* Eliminacija disjunkcije *)
thm impI           (* Uvodjenje implikacije *)
thm impE           (* Eliminacija implikacije *)
thm mp             (* Modus ponens *)
thm classical      (* Teorema klasicne logike *)
thm ccontr         (* Kontradikcija (klasicna logika) *)


lemma "A \<and> B \<longrightarrow> B \<and> A"
apply (rule impI)
apply (rule conjI)
apply (erule conjE)
apply assumption
apply (erule conjE)
apply assumption
done


lemma "A \<or> B \<longrightarrow> B \<or> A"
apply (rule impI)
apply (erule disjE)
apply (rule disjI2)
apply assumption
apply (rule disjI1)
apply assumption
done


lemma "A \<or> (B \<or> C) \<longrightarrow> (A \<or> B) \<or> C"
apply (rule impI)
apply (erule disjE)
apply (rule disjI1)
apply (rule disjI1)
apply assumption
apply (erule disjE)
apply (rule disjI1)
apply (rule disjI2)
apply assumption
apply (rule disjI2)
apply assumption
done


lemma "A \<and> (B \<and> C) \<longrightarrow> (A \<and> B) \<and> C"
apply (rule impI)
apply (erule conjE)
apply (erule conjE)
apply (rule conjI)
apply (rule conjI)
apply assumption
apply assumption
apply assumption
done


lemma "A \<and> (B \<or> C) \<longrightarrow> (A \<and> B) \<or> (A \<and> C)"
apply (rule impI)
apply (erule conjE)
apply (erule disjE)
apply (rule disjI1)
apply (rule conjI)
apply assumption
apply assumption
apply (rule disjI2)
apply (rule conjI)
apply assumption
apply assumption
done


lemma "((A \<and> B) \<or> (A \<and> C)) \<longrightarrow> (A \<and> (B \<or> C))"
apply (rule impI)
apply (rule conjI)
apply (erule disjE)
apply (erule conjE)
apply assumption
apply (erule conjE)
apply assumption
apply (erule disjE)
apply (rule disjI1)
apply (erule conjE)
apply assumption
apply (rule disjI2)
apply (erule conjE)
apply assumption
done


lemma "A \<or> (B \<and> C) \<longrightarrow> (A \<or> B) \<and> (A \<or> C)"
apply (rule impI)
apply (erule disjE)
apply (rule conjI)
apply (rule disjI1)
apply assumption
apply (rule disjI1)
apply assumption
apply (rule conjI)
apply (rule disjI2)
apply (erule conjE)
apply assumption
apply (rule disjI2)
apply (erule conjE)
apply assumption
done


lemma "((A \<or> B) \<and> (A \<or> C)) \<longrightarrow> (A \<or> (B \<and> C))"
apply (rule impI)
apply (erule conjE)
apply (erule disjE)
apply (rule disjI1)
apply assumption
apply (erule disjE)
apply (rule disjI1)
apply assumption
apply (rule disjI2)
apply (rule conjI)
apply assumption
apply assumption
done


lemma "(\<not>A \<and> (A \<or> B)) \<longrightarrow> B"
apply (rule impI)
apply (rule ccontr)
apply (erule conjE)
apply (erule disjE)
apply (erule_tac ?P="A" in notE)
apply assumption
apply (erule notE)
apply assumption
done

lemma "A \<longrightarrow> (B \<longrightarrow> A)"
apply (rule impI)
apply (rule impI)
apply assumption
done


lemma "(A \<longrightarrow> B) \<longrightarrow> (\<not>B \<longrightarrow> \<not>A)"
apply (rule impI)
apply (rule impI)
apply (rule notI)
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
done


lemma "(\<not>B \<longrightarrow> \<not>A) \<longrightarrow> (A \<longrightarrow> B)"
apply (rule impI)
apply (rule impI)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule_tac ?P="A" in notE)
apply assumption
done

lemma "((A \<longrightarrow> B) \<and> (B \<longrightarrow> C)) \<longrightarrow> (A \<longrightarrow> C)"
apply (rule impI)
apply (erule conjE)
apply (rule impI)
apply (erule impE)
apply assumption
apply (erule impE)
apply assumption
apply assumption
done


lemma "A \<longrightarrow> \<not>\<not>A"
apply (rule impI)
apply (rule notI)
apply (erule notE)
apply assumption
done


lemma "\<not>\<not>A \<longrightarrow> A"
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply assumption
done


lemma "\<not>(A \<or> B) \<longrightarrow> (\<not>A \<and> \<not>B)"
apply (rule impI)
apply (rule conjI)
apply (rule notI)
apply (erule notE)
apply (rule disjI1)
apply assumption
apply (rule notI)
apply (erule notE)
apply (rule disjI2)
apply assumption
done


lemma "(\<not>A \<and> \<not>B) \<longrightarrow> \<not>(A \<or> B)"
apply (rule impI)
apply (rule notI)
apply (erule conjE)
apply (erule disjE)
apply (erule notE)
apply (assumption)
apply (erule_tac ?P="B" in notE)
apply assumption
done

lemma "\<not>(A \<and> B) \<longrightarrow> (\<not>A \<or> \<not>B)"
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule conjI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply assumption
apply (rule ccontr)
apply (erule notE)
apply (rule disjI2)
apply assumption
done


lemma "(\<not>A \<or> \<not>B) \<longrightarrow> \<not>(A \<and> B)"
apply (rule impI)
apply (erule disjE)
apply (rule notI)
apply (erule conjE)
apply (erule notE)
apply assumption
apply (rule notI)
apply (erule conjE)
apply (erule notE)
apply assumption
done


lemma "(A \<longrightarrow> (B \<longrightarrow> C)) \<longrightarrow> ((A \<and> B) \<longrightarrow> C)"
apply (rule impI)
apply (rule impI)
apply (rule ccontr)
apply (erule conjE)
apply (erule impE)
apply assumption
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
done


lemma "((A \<longrightarrow> C) \<and> (B \<longrightarrow> C) \<and> (A \<or> B)) \<longrightarrow> C"
apply (rule impI)
apply (erule conjE)
apply (erule conjE)
apply (erule disjE)
apply (erule impE)
apply assumption
apply assumption
apply (erule_tac ?P="B" in impE)
apply assumption
apply assumption
done

lemma "((A \<longrightarrow> B) \<and> (A \<longrightarrow> C)) \<longrightarrow> (A \<longrightarrow> (B \<and> C))"
apply (rule impI)
apply (rule impI)
apply (erule conjE)
apply (erule impE)
apply assumption
apply (rule conjI)
apply assumption
apply (erule impE)
apply assumption
apply assumption
done


lemma "A \<or> \<not> A"
apply (rule ccontr)
apply (rule_tac ?P="A" in  notE)
apply (rule notI)
apply (erule notE)
apply (rule disjI1)
apply assumption
apply (rule ccontr)
apply (erule notE)
apply (rule disjI2)
apply assumption
done


lemma "(\<not>A \<longrightarrow> A) \<longrightarrow> A"
apply (rule impI)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
done


lemma "((A \<or> B) \<and> (\<not>A \<or> \<not>B) \<longrightarrow> A) \<longrightarrow> (B \<longrightarrow> A)"
apply (rule impI)
apply (rule impI)
apply (rule ccontr)
apply (erule impE)
apply (rule conjI)
apply (rule disjI2)
apply assumption
apply (rule disjI1)
apply assumption
apply (erule_tac ?P="A" in notE)
apply assumption
done


lemma "((A \<longrightarrow> B) \<and> (\<not>A \<longrightarrow> B)) \<longrightarrow> B"
apply (rule impI)
apply (erule conjE)
apply (rule ccontr)
apply (erule impE)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
apply (erule_tac ?P="B" in notE)
apply assumption
done

lemma "(\<not>B \<longrightarrow> \<not>A) \<longrightarrow> ((B \<or> A) \<longrightarrow> B)"   (* Kolokvijum 2011 *)
apply (rule impI)
apply (rule impI)
apply (erule disjE)
apply assumption
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule_tac ?P="A" in notE)
apply assumption
done


lemma "(\<not>B \<longrightarrow> (A \<longrightarrow> B)) \<and> (\<not>B \<longrightarrow> (A \<or> B)) \<longrightarrow> B" (* Kolokvijum 2012 *)
apply (rule impI)
apply (erule conjE)
apply (rule ccontr)
apply (erule impE)
apply assumption
apply (erule impE)
apply assumption
apply (erule disjE)
apply (erule impE)
apply assumption
apply (erule notE)
apply assumption
apply (erule notE)
apply assumption
done


lemma "\<not>((p \<longrightarrow> q) \<and> (\<not>r \<or> s)) \<longrightarrow> ((p \<and> \<not>q) \<or> (r \<and> \<not>s))" (* Kolokvijum 2013 *)
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule conjI)
apply (rule impI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply (rule conjI)
apply assumption
apply assumption
apply (rule ccontr)
apply (erule notE)
apply (rule disjI2)
apply (rule ccontr)
apply (erule_tac ?P="r \<and> \<not>s" in notE)
apply (rule conjI)
apply (rule ccontr)
apply (erule notE)
apply (rule disjI1)
apply assumption
apply (rule notI)
apply (erule notE)
apply (rule disjI2)
apply assumption
done

end
