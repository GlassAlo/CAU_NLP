# 📐 Vector Space Information Retrieval System

A minimal and efficient Vector Space Model (VSM)-based search engine implemented in C++. This system demonstrates document ranking using **TF-IDF** and **cosine similarity**, a foundational concept in modern information retrieval.

---

## 🚀 Features

- Preprocessing: tokenization, normalization, stopword filtering
- Term-document TF-IDF matrix generation
- Query vector construction and scoring
- Cosine similarity computation for ranked results
- Fully modular, easy to extend with your own datasets

---

## 🔎 How It Works

1. **Document Preprocessing**  
   Each document is converted into a list of lowercase tokens, with optional stopword removal and basic stemming.

2. **TF-IDF Computation**  
   - **TF**: Term frequency within a document  
   - **IDF**: Inverse document frequency across the collection  
   - The product of TF and IDF gives each term a weight.

3. **Query Vector Construction**  
   A query is treated like a mini document. The same TF-IDF process is applied.

4. **Similarity Calculation**  
   Documents are ranked based on the **cosine similarity** between their vector and the query vector.

---

## 🧠 What You’ll Learn

- The mathematics behind TF-IDF
- Vector space representations of text
- How cosine similarity works to score relevance
- A modular approach to building IR engines

---

## Run

```bash
./vector_ir
```

---

---

## 🧪 Example

**Documents:**

```
[0] Lamborghini Diablo and Ferrari F50 are legendary cars.
[1] Porsche 959 was a technological marvel.
[2] Racing games include classic cars like Ferrari and Lamborghini.
```

**Query:**

```
ferrari lamborghini
```

**Results (Ranked by Similarity):**

```
[2] Score: 0.71
[0] Score: 0.65
[1] Score: 0.00
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 👤 Author

Crafted by Maxence Labourel — Feel free to ⭐ the project, fork it, and contribute!

---
