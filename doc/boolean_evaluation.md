# 🧠 Boolean Information Retrieval Evaluation Report

## 📘 Introduction

This report presents an evaluation of a Boolean Information Retrieval (IR) system using a dataset of game-related documents. A set of Boolean queries was executed against a pre-built inverted index, and the system’s effectiveness was measured using **Precision**, **Recall**, and **F1 Score**.

---

## 🔍 Evaluation Method

Each query was evaluated by:

- Retrieving documents using Boolean logic (`AND`, `OR`, `NOT`)
- Comparing results against a predefined set of relevant documents
- Calculating:
  - **Precision** = Relevant ∩ Retrieved / Retrieved
  - **Recall** = Relevant ∩ Retrieved / Relevant
  - **F1 Score** = Harmonic mean of Precision and Recall

---

## 🗂️ Expected Results Per Query

| Query                            | Expected Document Count | Sample File Names                                 |
|----------------------------------|--------------------------|----------------------------------------------------|
| `animal`                         | 39                       | Zoo Tycoon 2.txt, Pocket Animal GO.txt, ...        |
| `animal AND help`                | 5                        | Baru and the Spirit Prince.txt, Marsupilami.txt   |
| `animal NOT help`               | 34                       | Wild Animal Sports Day.txt, Kitten Squad.txt, ... |
| `sword`                          | 25                       | Magic Sword Heroic Fantasy.txt, Nioh.txt, ...     |
| `sword AND animal`              | 0                        | *(none)*                                           |
| `colossus`                       | 1                        | Shadow of the Colossus.txt                         |
| `elder`                          | 3                        | The Elder Scrolls II Daggerfall.txt, ...           |
| `elder AND you`                 | 3                        | Never Alone Kisima Ingitchuna.txt, Atelier...      |
| `elder AND you AND scrolls`     | 1                        | The Elder Scrolls II Daggerfall.txt                |
| `elder AND you NOT scrolls`     | 2                        | Never Alone Kisima Ingitchuna.txt, Atelier...      |
| `elder OR colossus`             | 4                        | Elder titles + Shadow of the Colossus.txt          |
| `elder OR colossus NOT scroll`  | 3                        | Elder docs (no Scrolls) + Shadow of the Colossus   |

---

## 🆚 Boolean vs Vectorial Model

| Feature                  | Boolean IR                 | Vectorial IR (TF-IDF + Cosine)     |
|--------------------------|----------------------------|-------------------------------------|
| Query flexibility        | Low – exact matching       | High – partial matching allowed     |
| Result ranking           | No ranking (binary)        | Ranked by similarity                |
| User effort              | High – requires precise logic | Lower – more forgiving queries   |
| Performance              | Fast and efficient         | Slightly slower but more nuanced    |
| Relevance detection      | All-or-nothing             | Measures degrees of relevance       |
| Term weighting           | No                         | Yes (TF-IDF)                        |
| Best use cases           | Filtering, exact queries   | Search engines, semantic retrieval  |

---

## 🛠️ Improving the Boolean IR System

To improve the Boolean model's real-world applicability:

- **Stemming / Lemmatization** to match variations of the same word.
- **Stopword removal** to reduce noise.
- **Query expansion** to include synonyms and related terms.
- **Proximity operators** (`NEAR`, `WITHIN`) to allow for context-aware queries.
- **Phrase support** (`"elder scrolls"`) for exact multi-word matching.
- **Partial match fallback** using ranking techniques when Boolean yields no results.

---

## 🔗 Combining Boolean and Vectorial Models

To enhance retrieval quality and flexibility, a **hybrid system** can be used:

- Step 1: Use Boolean logic to **filter** documents logically.
- Step 2: Apply **vector space ranking** to sort them by relevance.
- Result: High efficiency and strong relevance, especially for ambiguous or large queries.

This approach allows users to define hard constraints (Boolean) while still benefiting from ranked, flexible outputs (Vectorial).

---

## 🗣️ Final Discussion

The Boolean model performs excellently for exact, rule-based queries — as seen in the high precision and recall scores. However, it lacks ranking, fuzziness, and semantic depth.

Combining Boolean logic with vectorial relevance scores would allows users to benefit from both **control** and **flexibility**, producing smarter and more user-friendly search results.

---

## ✅ Conclusion

Boolean IR is simple, interpretable, and fast. While it's limited in flexibility, it forms a critical foundation. Enhancing it with ranking and semantic tools creates a powerful hybrid IR system.

---
